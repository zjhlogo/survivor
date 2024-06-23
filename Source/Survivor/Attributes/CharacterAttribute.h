// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttribute.h"
#include "CharacterAttribute.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVOR_API UCharacterAttribute : public UBaseAttribute
{
	GENERATED_BODY()

protected:
	virtual bool OnPostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

public:
	// 每秒恢复多少点血量
	ATTRIBUTE_ACCESSORS(UCharacterAttribute, RecoveryHp);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData RecoveryHp;

	// 拾取范围
	ATTRIBUTE_ACCESSORS(UCharacterAttribute, PickupRange);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData PickupRange;

	// 局外武器伤害加成
	ATTRIBUTE_ACCESSORS(UCharacterAttribute, ExternalDamageFactor);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData ExternalDamageFactor;
	
	// 局内武器伤害加成
	ATTRIBUTE_ACCESSORS(UCharacterAttribute, InternalDamageFactor);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData InternalDamageFactor;
	
	// 暴击伤害
	ATTRIBUTE_ACCESSORS(UCharacterAttribute, CriticalDamage);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData CriticalDamage;

	// 换弹速度
	ATTRIBUTE_ACCESSORS(UCharacterAttribute, ReloadSpeed);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData ReloadSpeed;

	// 闪避几率
	ATTRIBUTE_ACCESSORS(UCharacterAttribute, DodgeProbability);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData DodgeProbability;

	// 暴击几率
	ATTRIBUTE_ACCESSORS(UCharacterAttribute, CriticalDamageProbability);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData CriticalDamageProbability;

	// 当前经验
	ATTRIBUTE_ACCESSORS(UCharacterAttribute, Exp);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData Exp;

	// 经验加成
	ATTRIBUTE_ACCESSORS(UCharacterAttribute, ExpFactor);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData ExpFactor;

	// 当前等级
	ATTRIBUTE_ACCESSORS(UCharacterAttribute, Level);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData Level;

	// 运气
	ATTRIBUTE_ACCESSORS(UCharacterAttribute, Lucky);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData Lucky;
};
