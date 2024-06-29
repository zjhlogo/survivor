// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Survivor/Actors/ItemBase.h"
#include "Survivor/Attributes/MonsterAttribute.h"
#include "Survivor/Character/SurvivorCharacter.h"
#include "Survivor/Systems/ConfigSystem.h"
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

const FMonsterConfig* AMonsterBase::GetMonsterConfig() const
{
	return UConfigSystem::Get()->FindMonsterConfig(MonsterConfig.RowName);
}

void AMonsterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (!FSurvivorDefine::IsGameRunning())
	{
		return;
	}

	// reset attributes
	auto MonsterCfg = UConfigSystem::Get()->FindMonsterConfig(MonsterConfig.RowName);
	check(MonsterCfg);

	MonsterAttribute = NewObject<UMonsterAttribute>(this);
	MonsterAttribute->InitHp(MonsterCfg->BaseHp);
	MonsterAttribute->InitMaxHp(MonsterCfg->BaseHp);
	MonsterAttribute->InitBaseDamage(MonsterCfg->BaseDamage);
	AbilitySystem->AddSpawnedAttribute(MonsterAttribute);
	AbilitySystem->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FSurvivorDefine::AttributeTagMonster));

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
		DeathSpawn();
		GetCapsuleComponent()->SetCollisionProfileName(FSurvivorDefine::CollisionProfileNoCollision);
		OnMonsterDead.Execute(this);
		OnDead();
	}
}

void AMonsterBase::DeathSpawn()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;

	auto ItemBase = GetWorld()->SpawnActor<AItemBase>(ExpItemClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	ItemBase->SetSourceActor(this);
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
