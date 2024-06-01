// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserDamageEffect.h"

#include "Survivor/Attributes/BaseAttribute.h"

void ULaserDamageEffect::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	if (ensure(GWorld))
	{
		float Damage = GWorld->GetDeltaSeconds() * 50.0f;
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UBaseAttribute::GetHpAttribute(), EGameplayModOp::Additive, -Damage));
	}
}
