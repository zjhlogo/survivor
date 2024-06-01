// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Survivor/Hud/HealthBarWidget.h"
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

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(RootComponent);
	
	// Create ASC
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetOwnerActor(this);
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	// bind event
	UHealthBarWidget* HealthBarWidget = Cast<UHealthBarWidget>(HealthBar->GetWidget());
	if (ensure(HealthBarWidget))
	{
		HealthBarWidget->BindEvents(this);
	}
}
