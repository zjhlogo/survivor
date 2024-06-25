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

UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ECharacterState: uint64
{
	None = 0 UMETA(Hidden),
	Dead = 1 << 0,
};

ENUM_CLASS_FLAGS(ECharacterState);

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

	// 移动速度
	ATTRIBUTE_ACCESSORS(UBaseAttribute, MoveSpeed);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData MoveSpeed;

	// internal states
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	ECharacterState State{ECharacterState::None};
};
