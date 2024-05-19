// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserAbility.h"

#include "Survivor/Actors/LaserBase.h"

void ULaserAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                    const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo,
                                    const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// spawn laser beams
	AActor* Actor = GetAvatarActorFromActorInfo();
	if (!Actor)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	int NumLaserToFire = LineCount;
	double StepRotation = 360.0 / NumLaserToFire;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = Actor;
	SpawnParams.Instigator = Cast<APawn>(Actor);

	FVector ActorPos = Actor->GetActorLocation();
	for (int i = 0; i < NumLaserToFire; ++i)
	{
		FTransform SpawnTrans = FTransform(FRotator(0.0, StepRotation * i, 0.0), ActorPos);
		// spawn laser
		ALaserBase* Laser = World->SpawnActor<ALaserBase>(LaserClass, SpawnTrans, SpawnParams);
		Laser->SetAutoRotateParameter(bRotate, StepRotation * i, RotateSpeed);
		SpawnedLaserList.Add(Laser);
	}

	CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, false);
}

void ULaserAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                               const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilityActivationInfo ActivationInfo,
                               bool bReplicateEndAbility,
                               bool bWasCancelled)
{
	// remove laser beams
	for (ALaserBase* Laser : SpawnedLaserList)
	{
		Laser->Destroy();
	}
	SpawnedLaserList.Empty();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
