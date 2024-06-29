// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletDamageEffect.h"

#include "Survivor/Attributes/PawnBaseAttribute.h"
#include "Survivor/Attributes/CharacterAttribute.h"
#include "Survivor/Systems/ConfigSystem.h"
#include "Survivor/Config/WeaponBulletLevelConfig.h"

void UBulletDamageEffect::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                 FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	auto SourceAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	// auto TargetAsc = ExecutionParams.GetTargetAbilitySystemComponent();

	// auto CharacterLevel = static_cast<int32>(SourceAsc->GetNumericAttribute(UCharacterAttribute::GetLevelAttribute()));
	// auto LevelCfg = ConfigSystem->FindCharacterLevelConfig(CharacterLevel);

	const FWeaponBulletLevelConfig* WeaponLevelConfig = nullptr;
	if (WeaponCategory == 1)
	{
		auto WeaponLevel = static_cast<int32>(SourceAsc->GetNumericAttribute(UCharacterAttribute::GetWeaponLevelCat1Attribute()));
		WeaponLevelConfig = UConfigSystem::Get()->FindWeaponBulletLevelConfig(WeaponCategory, WeaponLevel);
	}
	else if (WeaponCategory == 2)
	{
		auto WeaponLevel = static_cast<int32>(SourceAsc->GetNumericAttribute(UCharacterAttribute::GetWeaponLevelCat2Attribute()));
		WeaponLevelConfig = UConfigSystem::Get()->FindWeaponBulletLevelConfig(WeaponCategory, WeaponLevel);
	}

	if (WeaponLevelConfig == nullptr)
	{
		return;
	}

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UPawnBaseAttribute::GetHpAttribute(),
	                                                                    EGameplayModOp::Additive,
	                                                                    -WeaponLevelConfig->BaseDamage));
}
