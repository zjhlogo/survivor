// Copyright Epic Games, Inc. All Rights Reserved.

#include "SurvivorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
#include "Survivor/Enemy/EnemyBase.h"
#include "Survivor/Ability/SurvivorBaseAbility.h"
#include "Survivor/Util/SurvivorDefine.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

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

void ASurvivorCharacter::BeginPlay()
{
	Super::BeginPlay();

	// gain abilities on birth
	for (TSubclassOf<USurvivorBaseAbility>& Ability : GainAbilitiesOnBirth)
	{
		FGameplayAbilitySpecHandle Handle = AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
		if (Ability.GetDefaultObject()->IsPassive())
		{
			AbilitySystem->TryActivateAbility(Handle);
		}
	}

	AbilitySystem->GetGameplayAttributeValueChangeDelegate(UBaseAttribute::GetHpAttribute()).AddUObject(this, &ASurvivorCharacter::OnHpChanged);
}

void ASurvivorCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (TSubclassOf<USurvivorBaseAbility>& Ability : GainAbilitiesOnBirth)
	{
		auto DefaultObj = Ability.GetDefaultObject();
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
