// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttribute.h"
#include "PawnBaseAttribute.generated.h"

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
class SURVIVOR_API UPawnBaseAttribute : public UBaseAttribute
{
	GENERATED_BODY()

protected:
	virtual bool OnPostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

public:
	// 当前血量
	ATTRIBUTE_ACCESSORS(UPawnBaseAttribute, Hp);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData Hp;

	// 最大血量
	ATTRIBUTE_ACCESSORS(UPawnBaseAttribute, MaxHp);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData MaxHp;

	// 移动速度
	ATTRIBUTE_ACCESSORS(UPawnBaseAttribute, MoveSpeed);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData MoveSpeed;

	// internal states
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	ECharacterState State{ECharacterState::None};
};
