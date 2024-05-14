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
	UFUNCTION()
	bool IsPassive() const;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	bool IsPassiveAbility{};
};
