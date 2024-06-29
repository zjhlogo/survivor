// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttribute.h"
#include "WeaponLaserAttribute.generated.h"


/**
 * 
 */
UCLASS()
class SURVIVOR_API UWeaponLaserAttribute : public UBaseAttribute
{
	GENERATED_BODY()

public:
	// 激光伤害加成
	ATTRIBUTE_ACCESSORS(UWeaponLaserAttribute, DamageFactor);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData DamageFactor;

	// 线数
	ATTRIBUTE_ACCESSORS(UWeaponLaserAttribute, NumLine);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData NumLine;
};
