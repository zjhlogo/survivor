// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "SurvivorAbilityTask.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVOR_API USurvivorAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,
		Category="Ability|Tasks",
		meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static USurvivorAbilityTask* NewSurvivorAbilityTask(UGameplayAbility* OwningAbility, TSubclassOf<USurvivorAbilityTask> AbilityTaskClass);
};
