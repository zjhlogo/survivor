// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Survivor/Actors/ItemBase.h"
#include "Survivor/Attributes/BaseAttribute.h"
#include "Survivor/Character/SurvivorCharacter.h"
#include "Survivor/Ui/SurvivorWidgetBase.h"
#include "Survivor/Util/SurvivorDefine.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);

	// Create ASC
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetOwnerActor(this);

	bIsDead = false;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	// bind events
	AbilitySystem->GetGameplayAttributeValueChangeDelegate(UBaseAttribute::GetHpAttribute()).AddUObject(this, &AEnemyBase::OnHpChanged);

	if (USurvivorWidgetBase* WidgetBase = Cast<USurvivorWidgetBase>(HealthBarWidget->GetWidget()))
	{
		WidgetBase->OnBindEvent(this);
	}

	if (GeCastToCharacter.GetDefaultObject() != nullptr)
	{
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlappedWithCharacter);
	}
}

void AEnemyBase::OnHpChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0.0f && !bIsDead)
	{
		bIsDead = true;
		SpawnExp();
		GetCapsuleComponent()->SetCollisionProfileName(FSurvivorDefine::CollisionProfileNoCollision);
		OnDead();
	}
}

void AEnemyBase::SpawnExp()
{
	GetWorld()->SpawnActor<AItemBase>(ExpItemClass, GetActorLocation(), GetActorRotation());
}

void AEnemyBase::OnOverlappedWithCharacter(UPrimitiveComponent* OverlappedComponent,
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
