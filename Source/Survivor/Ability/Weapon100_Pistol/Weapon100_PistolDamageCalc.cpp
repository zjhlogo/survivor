// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon100_PistolDamageCalc.h"

#include "Weapon100_PistolAttribute.h"
#include "Survivor/Attributes/PawnBaseAttribute.h"
#include "Survivor/Attributes/CharacterAttribute.h"
#include "Survivor/Config/Weapon/Weapon100_PistolConfig.h"
#include "Survivor/Systems/WeaponConfigSystem.h"

void UWeapon100_PistolDamageCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                         FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	auto CharacterAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	auto MonsterAsc = ExecutionParams.GetTargetAbilitySystemComponent();

	auto WeaponLevel = static_cast<int32>(CharacterAsc->GetNumericAttribute(UWeapon100_PistolAttribute::GetLevelAttribute()));
	const FWeapon100_PistolConfig* WeaponConfig = UWeaponConfigSystem::Get().FindWeapon100_PistolConfig(WeaponLevel);
	if (WeaponConfig == nullptr)
	{
		return;
	}

	// 伤害 = 基础伤害 * （1.0f + 局内伤害加成 + 子弹类型武器额外加成 + 物理伤害加成）
	float IntDamageFactor = CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetInternalDamageFactorAttribute());
	float ExtDamageFactor = CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetExternalDamageFactorAttribute());
	float PhysicsDamageFactor = CharacterAsc->GetNumericAttribute(UCharacterAttribute::GetPhysicsDamageFactorAttribute());
	float Damage = WeaponConfig->Damage * (1.0f + IntDamageFactor + ExtDamageFactor + PhysicsDamageFactor);
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UPawnBaseAttribute::GetHpAttribute(), EGameplayModOp::Additive, -Damage));
}
