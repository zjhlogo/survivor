// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Survivor/Actors/ItemBase.h"
#include "Survivor/Attributes/BaseAttribute.h"
#include "Survivor/Ui/SurvivorWidgetBase.h"

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
}

void AEnemyBase::OnHpChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0.0f && !bIsDead)
	{
		bIsDead = true;
		SpawnExp();
		OnDead();
	}
}

void AEnemyBase::SpawnExp()
{
	GetWorld()->SpawnActor<AItemBase>(ExpItemClass, GetActorLocation(), GetActorRotation());
}
