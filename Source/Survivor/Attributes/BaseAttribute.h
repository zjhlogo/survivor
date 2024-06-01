// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseAttribute.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class SURVIVOR_API UBaseAttribute : public UAttributeSet
{
	GENERATED_BODY()

protected:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual bool OnPostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data);

public:
	// 当前血量
	ATTRIBUTE_ACCESSORS(UBaseAttribute, Hp);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData Hp;

	// 最大血量
	ATTRIBUTE_ACCESSORS(UBaseAttribute, MaxHp);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData MaxHp;

	// 护盾
	ATTRIBUTE_ACCESSORS(UBaseAttribute, Shield);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData Shield;

	// 伤害
	ATTRIBUTE_ACCESSORS(UBaseAttribute, Damage);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData Damage;

	// 移动速度
	ATTRIBUTE_ACCESSORS(UBaseAttribute, MoveSpeed);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData MoveSpeed;
};
