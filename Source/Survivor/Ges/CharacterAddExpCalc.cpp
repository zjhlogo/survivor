// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAddExpCalc.h"

#include "Survivor/Actors/ItemBase.h"
#include "Survivor/Attributes/CharacterAttribute.h"
#include "Survivor/Attributes/PawnBaseAttribute.h"
#include "Survivor/Config/MonsterConfig.h"
#include "Survivor/Systems/ConfigSystem.h"

void UCharacterAddExpCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                  FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	auto ItemAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	auto CharacterAsc = ExecutionParams.GetTargetAbilitySystemComponent();

	AItemBase* ItemActor = Cast<AItemBase>(ItemAsc->GetOwnerActor());
	check(ItemActor);

	if (const FMonsterConfig* MonsterCfg = UConfigSystem::Get()->FindMonsterConfig(ItemActor->GetSourceMonsterId()))
	{
		float ExpFactor = CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetExpFactorAttribute());
		float ExpToAdd = MonsterCfg->DropExp * (1.0f + ExpFactor);
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UCharacterAttribute::GetExpAttribute(), EGameplayModOp::Additive, ExpToAdd));
	}
}
