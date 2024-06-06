// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

#include "AbilitySystemComponent.h"
#include "Survivor/Util/DebugUtil.h"
#include "Survivor/Util/SurvivorDefine.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetCollisionProfileName(FSurvivorDefine::CollisionProfileItem);
	StaticMeshComp->CanCharacterStepUpOn = ECB_No;
}

void AItemBase::FlyToPawn(TObjectPtr<APawn> Pawn)
{
	StaticMeshComp->SetCollisionProfileName(FSurvivorDefine::CollisionProfileNoCollision);
	SetActorTickEnabled(true);
	PawnCollector = Pawn;
	ElapsedTime = 0.0f;
}

void AItemBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!PawnCollector)
	{
		return;
	}

	FVector CurrPos = GetActorLocation();
	FVector TargetPos = PawnCollector->GetActorLocation();
	FVector DistVec = TargetPos - CurrPos;
	if (DistVec.Length() < MinPickedDist)
	{
		// apply item pick effect
		if (UGameplayEffect* ClassInstance = PickedGe.GetDefaultObject())
		{
			if (UAbilitySystemComponent* Ability = PawnCollector->FindComponentByClass<UAbilitySystemComponent>())
			{
				Ability->ApplyGameplayEffectToSelf(ClassInstance, 0, {});
			}
		}

		Destroy();
	}

	ElapsedTime += DeltaSeconds;
	float CurrSpeed = FlyingSpeedCurve->GetFloatValue(ElapsedTime);
	SetActorLocation(CurrPos + CurrSpeed * DistVec.GetSafeNormal());
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);
}
