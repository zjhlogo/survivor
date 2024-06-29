// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponLaserDamageCalc.h"

#include "Survivor/Attributes/PawnBaseAttribute.h"

void UWeaponLaserDamageCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	auto CharacterAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	auto MonsterAsc = ExecutionParams.GetTargetAbilitySystemComponent();

	// const FWeaponBulletLevelConfig* WeaponLevelConfig = nullptr;
	// if (WeaponCategory == 1)
	// {
	// 	auto WeaponLevel = static_cast<int32>(CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetWeaponLevelCat1Attribute()));
	// 	WeaponLevelConfig = UConfigSystem::Get()->FindWeaponBulletLevelConfig(WeaponCategory, WeaponLevel);
	// }
	// else if (WeaponCategory == 2)
	// {
	// 	auto WeaponLevel = static_cast<int32>(CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetWeaponLevelCat2Attribute()));
	// 	WeaponLevelConfig = UConfigSystem::Get()->FindWeaponBulletLevelConfig(WeaponCategory, WeaponLevel);
	// }
	//
	// if (WeaponLevelConfig == nullptr)
	// {
	// 	return;
	// }
	//
	// // 伤害 = 武器伤害 * （局内伤害加成 + 子弹类型武器额外加成）
	// float IntDamageFactor = CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetInternalDamageFactorAttribute());
	// float ExtDamageFactor = CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetExternalDamageFactorAttribute());
	// float BulletDamageFactor = CharacterAsc->GetNumericAttribute(UBulletWeaponAttribute::GetDamageFactorAttribute());
	// float Damage = WeaponLevelConfig->BaseDamage * (1.0f + IntDamageFactor + ExtDamageFactor + BulletDamageFactor);
	// OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UPawnBaseAttribute::GetHpAttribute(), EGameplayModOp::Additive, -Damage));
}
