// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorAbilityTask.h"

USurvivorAbilityTask* USurvivorAbilityTask::NewSurvivorAbilityTask(UGameplayAbility* OwningAbility, TSubclassOf<USurvivorAbilityTask> AbilityTaskClass)
{
	check(OwningAbility);

	USurvivorAbilityTask* MyObj = NewObject<USurvivorAbilityTask>(GetTransientPackage(), AbilityTaskClass);
	MyObj->InitTask(*OwningAbility, OwningAbility->GetGameplayTaskDefaultPriority());

	DebugRecordAbilityTaskCreatedByAbility(OwningAbility);

	// MyObj->InstanceName = InstanceName;
	return MyObj;
}
