// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageEffect.h"

#include "Survivor/Attributes/BaseAttribute.h"

void UDamageEffect::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                           FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UBaseAttribute::GetHpAttribute(), EGameplayModOp::Additive, -5.0f));
}
