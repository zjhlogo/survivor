// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "BulletDamageCalc.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVOR_API UBulletDamageCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	int32 WeaponCategory{1};
};
