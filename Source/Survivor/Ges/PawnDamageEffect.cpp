﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnDamageEffect.h"

#include "Survivor/Attributes/BaseAttribute.h"
#include "Survivor/Util/DebugUtil.h"

void UPawnDamageEffect::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                               FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	PRINT_R("Character Damaged: {0}", DamageAmount);
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UBaseAttribute::GetHpAttribute(), EGameplayModOp::Additive, DamageAmount));
}
