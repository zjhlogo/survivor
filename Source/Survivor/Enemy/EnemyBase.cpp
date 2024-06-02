// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Survivor/Attributes/BaseAttributeComponent.h"
#include "Survivor/Hud/SurvivorWidgetBase.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);

	// Create ASC
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetOwnerActor(this);

	BaseAttributeCom = CreateDefaultSubobject<UBaseAttributeComponent>(TEXT("BaseAttributeCom"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (USurvivorWidgetBase* WidgetBase = Cast<USurvivorWidgetBase>(HealthBarWidget->GetWidget()))
	{
		WidgetBase->OnBindEvent(this);
	}
}
