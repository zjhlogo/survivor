// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletDamageEffect.h"

#include "Survivor/Attributes/BaseAttribute.h"
#include "Survivor/Attributes/CharacterAttribute.h"
#include "Survivor/Config/ConfigSystem.h"
#include "Survivor/Config/WeaponBulletLevelConfig.h"

void UBulletDamageEffect::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                 FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	auto SourceAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	// auto TargetAsc = ExecutionParams.GetTargetAbilitySystemComponent();

	auto ConfigSystem = UConfigSystem::Get(SourceAsc);

	// auto CharacterLevel = static_cast<int32>(SourceAsc->GetNumericAttribute(UCharacterAttribute::GetLevelAttribute()));
	// auto LevelCfg = ConfigSystem->FindCharacterLevelConfig(CharacterLevel);

	const FWeaponBulletLevelConfig* WeaponLevelConfig = nullptr;
	if (WeaponCategory == 1)
	{
		auto WeaponLevel = static_cast<int32>(SourceAsc->GetNumericAttribute(UCharacterAttribute::GetWeaponLevelCat1Attribute()));
		WeaponLevelConfig = ConfigSystem->FindWeaponBulletLevelConfig(WeaponCategory, WeaponLevel);
	}
	else if (WeaponCategory == 2)
	{
		auto WeaponLevel = static_cast<int32>(SourceAsc->GetNumericAttribute(UCharacterAttribute::GetWeaponLevelCat2Attribute()));
		WeaponLevelConfig = ConfigSystem->FindWeaponBulletLevelConfig(WeaponCategory, WeaponLevel);
	}

	if (WeaponLevelConfig == nullptr)
	{
		return;
	}

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UBaseAttribute::GetHpAttribute(),
	                                                                    EGameplayModOp::Additive,
	                                                                    -WeaponLevelConfig->BaseDamage));
}
