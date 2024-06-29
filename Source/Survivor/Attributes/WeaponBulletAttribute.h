// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttribute.h"
#include "WeaponBulletAttribute.generated.h"


/**
 * 
 */
UCLASS()
class SURVIVOR_API UWeaponBulletAttribute : public UBaseAttribute
{
	GENERATED_BODY()

public:
	// 子弹伤害加成
	ATTRIBUTE_ACCESSORS(UWeaponBulletAttribute, DamageFactor);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData DamageFactor;

	// 线数
	ATTRIBUTE_ACCESSORS(UWeaponBulletAttribute, NumLine);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData NumLine;
};
