// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBaseAttribute.h"
#include "MonsterAttribute.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVOR_API UMonsterAttribute : public UPawnBaseAttribute
{
	GENERATED_BODY()

public:
	// 基础伤害
	ATTRIBUTE_ACCESSORS(UMonsterAttribute, BaseDamage);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData BaseDamage;

	// 掉落Exp
	ATTRIBUTE_ACCESSORS(UMonsterAttribute, DropExp);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData DropExp;
};
