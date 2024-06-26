// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Survivor/Actors/ItemBase.h"
#include "Survivor/Attributes/MonsterAttribute.h"
#include "Survivor/Character/SurvivorCharacter.h"
#include "Survivor/Config/ConfigSystem.h"
#include "Survivor/Config/MonsterConfig.h"
#include "Survivor/Ui/SurvivorWidgetComponent.h"
#include "Survivor/Util/SurvivorDefine.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthBarWidget = CreateDefaultSubobject<USurvivorWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);

	// Create ASC
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetOwnerActor(this);

	bIsDead = false;
}

void AMonsterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (!FSurvivorDefine::IsGameRunning())
	{
		return;
	}

	// reset attributes
	auto ConfigSystem = UConfigSystem::Get(this);
	auto Config = ConfigSystem->FindMonsterConfig(MonsterConfig.RowName);
	check(Config);

	MonsterAttribute = NewObject<UMonsterAttribute>(this);
	MonsterAttribute->InitHp(Config->BaseHp);
	MonsterAttribute->InitMaxHp(Config->BaseHp);
	MonsterAttribute->InitBaseDamage(Config->BaseDamage);
	AbilitySystem->AddSpawnedAttribute(MonsterAttribute);

	// bind events
	AbilitySystem->GetGameplayAttributeValueChangeDelegate(UPawnBaseAttribute::GetHpAttribute()).AddUObject(this, &AMonsterBase::OnHpChanged);

	if (GeCastToCharacter.GetDefaultObject() != nullptr)
	{
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMonsterBase::OnOverlappedWithCharacter);
	}
}

void AMonsterBase::OnHpChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0.0f && !bIsDead)
	{
		bIsDead = true;
		SpawnExp();
		GetCapsuleComponent()->SetCollisionProfileName(FSurvivorDefine::CollisionProfileNoCollision);
		OnMonsterDead.Execute(this);
		OnDead();
	}
}

void AMonsterBase::SpawnExp()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;

	auto ItemBase = GetWorld()->SpawnActor<AItemBase>(ExpItemClass, GetActorLocation(), GetActorRotation(), SpawnParams);
}

void AMonsterBase::OnOverlappedWithCharacter(UPrimitiveComponent* OverlappedComponent,
                                             AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp,
                                             int32 OtherBodyIndex,
                                             bool bFromSweep,
                                             const FHitResult& SweepResult)
{
	ASurvivorCharacter* Character = Cast<ASurvivorCharacter>(OtherActor);
	if (Character != nullptr)
	{
		UAbilitySystemComponent* CharacterAsc = Character->GetAbilitySystemComponent();
		AbilitySystem->ApplyGameplayEffectToTarget(GeCastToCharacter.GetDefaultObject(), CharacterAsc);
	}
}
