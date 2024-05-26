// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SurvivorBaseAbility.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVOR_API USurvivorBaseAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	USurvivorBaseAbility();

	UFUNCTION()
	FORCEINLINE bool IsPassive() const { return bIsPassiveAbility; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	uint8 bIsPassiveAbility : 1;
};
