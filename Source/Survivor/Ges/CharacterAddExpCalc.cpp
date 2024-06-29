// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAddExpCalc.h"

#include "Survivor/Actors/ItemBase.h"
#include "Survivor/Attributes/CharacterAttribute.h"
#include "Survivor/Attributes/PawnBaseAttribute.h"
#include "Survivor/Config/MonsterConfig.h"
#include "Survivor/Monster/MonsterBase.h"
#include "Survivor/Util/DebugUtil.h"

void UCharacterAddExpCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                  FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	auto ItemAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	auto CharacterAsc = ExecutionParams.GetTargetAbilitySystemComponent();

	AItemBase* ItemActor = Cast<AItemBase>(ItemAsc->GetOwnerActor());
	check(ItemActor);

	AMonsterBase* MonsterActor = Cast<AMonsterBase>(ItemActor->GetSourceActor());
	if (ensure(MonsterActor))
	{
		const FMonsterConfig* MonsterCfg = MonsterActor->GetMonsterConfig();
		check(MonsterCfg);

		float ExpToAdd = MonsterCfg->DropExp * CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetExpFactorAttribute());
		PRINT_B("Exp Add: {0}", ExpToAdd);
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UCharacterAttribute::GetExpAttribute(), EGameplayModOp::Additive, ExpToAdd));
	}
}
