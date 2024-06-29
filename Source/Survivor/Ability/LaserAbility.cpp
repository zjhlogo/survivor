// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserAbility.h"

#include "Survivor/Actors/LaserBase.h"
#include "Survivor/Attributes/WeaponLaserAttribute.h"
#include "Survivor/Util/SurvivorDefine.h"

void ULaserAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (!LaserAttribute)
	{
		LaserAttribute = NewObject<UWeaponLaserAttribute>(ActorInfo->OwnerActor.Get());
		LaserAttribute->InitNumLine(LineCount);
	}

	ActorInfo->AbilitySystemComponent->AddSpawnedAttribute(LaserAttribute);
	ActorInfo->AbilitySystemComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FSurvivorDefine::AttributeTagLaserWeapon));
}

void ULaserAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	if (LaserAttribute)
	{
		ActorInfo->AbilitySystemComponent->RemoveSpawnedAttribute(LaserAttribute);
		LaserAttribute = nullptr;
	}

	Super::OnRemoveAbility(ActorInfo, Spec);
}

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

	int NumLaserToFire = static_cast<int>(ActorInfo->AbilitySystemComponent->GetNumericAttribute(UWeaponLaserAttribute::GetNumLineAttribute()));
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
		Laser->SetLaserBeamMaxLength(LaserBeamMaxLength);
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
		if (Laser)
		{
			Laser->Destroy();
		}
	}
	SpawnedLaserList.Empty();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
