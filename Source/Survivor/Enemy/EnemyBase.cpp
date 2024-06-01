// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Survivor/Attributes/BaseAttributeComponent.h"
#include "Survivor/Hud/SurvivorWidgetBase.h"
#include "Survivor/Util/SurvivorDefine.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	RootComponent = Collision;
	Collision->SetCollisionProfileName(FSurvivorDefine::CollisionProfileEnemy);
	Collision->CanCharacterStepUpOn = ECB_No;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

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
