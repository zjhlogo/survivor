// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorBaseAbility.h"
#include "LineBulletAbility.generated.h"

class AProjectileBase;
/**
 * 
 */
UCLASS()
class SURVIVOR_API ULineBulletAbility : public USurvivorBaseAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	                             const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> BulletClass;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = survivor,
		meta = (AllowPrivateAccess = "true", ClampMin = "1", ClampMax = "5"))
	int LineCount{1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	uint8 bRotate : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true", EditCondition="bRotate"))
	double RotateSpeedInDegree{45.0};
};
