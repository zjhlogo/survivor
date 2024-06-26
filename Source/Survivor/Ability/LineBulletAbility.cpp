// Fill out your copyright notice in the Description page of Project Settings.


#include "LineBulletAbility.h"

#include "AbilitySystemComponent.h"
#include "Survivor/Actors/ProjectileBase.h"
#include "Survivor/Attributes/BulletWeaponAttribute.h"

void ULineBulletAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (!BulletAttribute)
	{
		BulletAttribute = NewObject<UBulletWeaponAttribute>(ActorInfo->OwnerActor.Get());
		BulletAttribute->InitNumLine(LineCount);
	}

	ActorInfo->AbilitySystemComponent->AddSpawnedAttribute(BulletAttribute);
}

void ULineBulletAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	if (BulletAttribute)
	{
		ActorInfo->AbilitySystemComponent->RemoveSpawnedAttribute(BulletAttribute);
		BulletAttribute = nullptr;
	}

	Super::OnRemoveAbility(ActorInfo, Spec);
}

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

	int NumBulletToFire = static_cast<int>(ActorInfo->AbilitySystemComponent->GetNumericAttribute(UBulletWeaponAttribute::GetNumLineAttribute()));
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
