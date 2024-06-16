// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletDamageEffect.h"

#include "Survivor/Attributes/BaseAttribute.h"

void UBulletDamageEffect::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                 FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UBaseAttribute::GetHpAttribute(), EGameplayModOp::Additive, DamageAmount));
}
