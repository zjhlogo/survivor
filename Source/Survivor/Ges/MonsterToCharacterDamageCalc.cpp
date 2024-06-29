// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterToCharacterDamageCalc.h"

#include "Survivor/Attributes/PawnBaseAttribute.h"
#include "Survivor/Config/MonsterConfig.h"
#include "Survivor/Monster/MonsterBase.h"

void UMonsterToCharacterDamageCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                           FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	auto MonsterAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	// auto CharacterAsc = ExecutionParams.GetTargetAbilitySystemComponent();

	AMonsterBase* MonsterActor = Cast<AMonsterBase>(MonsterAsc->GetAvatarActor());
	check(MonsterActor);

	const FMonsterConfig* MonsterConfig = MonsterActor->GetMonsterConfig();
	check(MonsterConfig);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UPawnBaseAttribute::GetHpAttribute(),
	                                                                    EGameplayModOp::Additive,
	                                                                    -MonsterConfig->BaseDamage));
}
