// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Survivor/Attributes/BaseAttribute.h"
#include "Weapon100_PistolAttribute.generated.h"


/**
 * 
 */
UCLASS()
class SURVIVOR_API UWeapon100_PistolAttribute : public UBaseAttribute
{
	GENERATED_BODY()

public:
	// 等级
	ATTRIBUTE_ACCESSORS(UWeapon100_PistolAttribute, Level);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FGameplayAttributeData Level{1.0f};
};
