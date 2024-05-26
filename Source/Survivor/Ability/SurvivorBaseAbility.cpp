// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorBaseAbility.h"

USurvivorBaseAbility::USurvivorBaseAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	bRetriggerInstancedAbility = true;
	bIsPassiveAbility = false;
}
