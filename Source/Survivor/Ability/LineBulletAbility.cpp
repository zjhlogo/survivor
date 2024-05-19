// Fill out your copyright notice in the Description page of Project Settings.


#include "LineBulletAbility.h"

#include "Survivor/Actors/ProjectileBase.h"

void ULineBulletAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// spawn bullets
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
	
	int NumBulletToFire = LineCount;
	double OffsetRotation = 0.0;
	if (bRotate)
	{
		// calculate new OffsetRotation
		double ElapseTime = FMath::Fmod(World->GetTimeSeconds(), 360.0);
		OffsetRotation = RotateSpeed * ElapseTime;
	}

	double StepRotation = 360.0 / NumBulletToFire;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = Actor;
	SpawnParams.Instigator = Cast<APawn>(Actor);

	FVector ActorPos = Actor->GetActorLocation();
	for (int i = 0; i < NumBulletToFire; ++i)
	{
		FTransform SpawnTrans = FTransform(FRotator(0.0, OffsetRotation + StepRotation * i, 0.0), ActorPos);
		// spawn bullet
		World->SpawnActor<AProjectileBase>(BulletClass, SpawnTrans, SpawnParams);
	}

	CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, false);
}
