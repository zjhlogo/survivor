// Copyright Epic Games, Inc. All Rights Reserved.

#include "SurvivorCharacter.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
#include "Survivor/Monster/MonsterBase.h"
#include "Survivor/Ability/SurvivorBaseAbility.h"
#include "Survivor/Util/SurvivorDefine.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Survivor/Attributes/CharacterAttribute.h"
#include "Survivor/Config/CharacterLevelConfig.h"
#include "Survivor/Config/ConfigSystem.h"

ASurvivorCharacter::ASurvivorCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// setup item picker
	ItemPicker = CreateDefaultSubobject<USphereComponent>(TEXT("ItemPicker"));
	ItemPicker->SetupAttachment(RootComponent);
	ItemPicker->InitSphereRadius(200.0f);
	ItemPicker->CanCharacterStepUpOn = ECB_No;
	ItemPicker->SetCollisionProfileName(FSurvivorDefine::CollisionProfileItemPicker);

	// Create ASC
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetOwnerActor(this);

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bIsDead = false;
}

void ASurvivorCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (!FSurvivorDefine::IsGameRunning())
	{
		return;
	}

	// reset attributes
	auto ConfigSystem = UConfigSystem::Get(this);
	auto LevelConfig = ConfigSystem->FindCharacterLevelConfig(1);
	check(LevelConfig);

	CharacterAttribute = NewObject<UCharacterAttribute>(this);
	CharacterAttribute->InitHp(LevelConfig->BaseHp);
	CharacterAttribute->InitMaxHp(LevelConfig->BaseHp);
	CharacterAttribute->InitLevel(1);
	CharacterAttribute->InitWeaponLevelCat1(1);
	AbilitySystem->AddSpawnedAttribute(CharacterAttribute);

	AbilitySystem->GetGameplayAttributeValueChangeDelegate(UPawnBaseAttribute::GetHpAttribute()).AddUObject(this, &ASurvivorCharacter::OnHpChanged);
	AbilitySystem->GetGameplayAttributeValueChangeDelegate(UCharacterAttribute::GetLevelAttribute()).AddUObject(this, &ASurvivorCharacter::OnLevelUp);
}

void ASurvivorCharacter::BeginPlay()
{
	Super::BeginPlay();

	// gain abilities on birth
	for (TSubclassOf<USurvivorBaseAbility>& Ability : GainAbilitiesOnBirth)
	{
		FGameplayAbilitySpecHandle Handle = AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
		AbilitySystem->TryActivateAbility(Handle);
	}
}

void ASurvivorCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (TSubclassOf<USurvivorBaseAbility>& Ability : GainAbilitiesOnBirth)
	{
		USurvivorBaseAbility* DefaultObj = Ability.GetDefaultObject();
		if (DefaultObj->IsPassive())
		{
			AbilitySystem->TryActivateAbilitiesByTag(DefaultObj->AbilityTags);
		}
	}
}

void ASurvivorCharacter::OnHpChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0.0f && !bIsDead)
	{
		bIsDead = true;
		OnDead();
	}
}

void ASurvivorCharacter::OnLevelUp(const FOnAttributeChangeData& Data)
{
	OnLevelUp();
}
