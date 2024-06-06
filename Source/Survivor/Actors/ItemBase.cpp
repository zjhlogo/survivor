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
		if (UAbilitySystemComponent* Ability = PawnCollector->FindComponentByClass<UAbilitySystemComponent>())
		{
			PRINT_G("gain exp");
			// Ability->ApplyGameplayEffectToSelf(PickedGe.GetDefaultObject(), 0, {});
		}

		Destroy();
	}

	SetActorLocation(CurrPos + FlyingSpeed * DeltaSeconds * DistVec);
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);
}
