// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBulletDamageCalc.h"

#include "Survivor/Attributes/WeaponBulletAttribute.h"
#include "Survivor/Attributes/PawnBaseAttribute.h"
#include "Survivor/Attributes/CharacterAttribute.h"
#include "Survivor/Systems/ConfigSystem.h"
#include "Survivor/Config/WeaponBulletLevelConfig.h"

void UWeaponBulletDamageCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                               FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	auto CharacterAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	auto MonsterAsc = ExecutionParams.GetTargetAbilitySystemComponent();

	const FWeaponBulletLevelConfig* WeaponLevelConfig = nullptr;
	if (WeaponCategory == 1)
	{
		auto WeaponLevel = static_cast<int32>(CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetWeaponLevelCat1Attribute()));
		WeaponLevelConfig = UConfigSystem::Get()->FindWeaponBulletLevelConfig(WeaponCategory, WeaponLevel);
	}
	else if (WeaponCategory == 2)
	{
		auto WeaponLevel = static_cast<int32>(CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetWeaponLevelCat2Attribute()));
		WeaponLevelConfig = UConfigSystem::Get()->FindWeaponBulletLevelConfig(WeaponCategory, WeaponLevel);
	}

	if (WeaponLevelConfig == nullptr)
	{
		return;
	}

	// 伤害 = 武器伤害 * （局内伤害加成 + 子弹类型武器额外加成）
	float IntDamageFactor = CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetInternalDamageFactorAttribute());
	float ExtDamageFactor = CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetExternalDamageFactorAttribute());
	float BulletDamageFactor = CharacterAsc->GetNumericAttribute(UWeaponBulletAttribute::GetDamageFactorAttribute());
	float Damage = WeaponLevelConfig->BaseDamage * (1.0f + IntDamageFactor + ExtDamageFactor + BulletDamageFactor);
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UPawnBaseAttribute::GetHpAttribute(), EGameplayModOp::Additive, -Damage));
}
