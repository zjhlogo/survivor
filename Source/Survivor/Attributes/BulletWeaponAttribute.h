// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttribute.h"
#include "BulletWeaponAttribute.generated.h"


/**
 * 
 */
UCLASS()
class SURVIVOR_API UBulletWeaponAttribute : public UBaseAttribute
{
	GENERATED_BODY()

public:
	// 子弹伤害加成
	ATTRIBUTE_ACCESSORS(UBulletWeaponAttribute, DamageFactor);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData DamageFactor;

	// 线数
	ATTRIBUTE_ACCESSORS(UBulletWeaponAttribute, NumLine);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData NumLine;
};
