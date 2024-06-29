// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FSurvivorDefine
{
public:
	inline static const FName CollisionProfileNoCollision{TEXT("NoCollision")};
	inline static const FName CollisionProfileCharacter{TEXT("Pawn")};
	inline static const FName CollisionProfileMonster{TEXT("Enemy")};
	inline static const FName CollisionProfileMonsterProjectile{TEXT("MonsterProjectile")};
	inline static const FName CollisionProfileCharacterProjectile{TEXT("CharacterProjectile")};
	inline static const FName CollisionProfileItem{TEXT("Item")};
	inline static const FName CollisionProfileItemPicker{TEXT("ItemPicker")};

	// gameplay tags
	inline static const FName AttributeTagBulletWeapon{TEXT("Attribute.BulletWeapon")};
	inline static const FName AttributeTagCharacter{TEXT("Attribute.Character")};
	inline static const FName AttributeTagMonster{TEXT("Attribute.Monster")};

	static bool IsGameRunning();

	static void CalculateAccumulateWeights(TArray<float>& OutAccumulateWeights, const TArray<float>& Weights);
	static int32 ChoiceByAccumulateWeights(const TArray<float>& AccumulateWeights);
	static int32 ChoiceByWeights(const TArray<float>& Weights);
	static bool ChoiceByAccumulateWeights(TArray<int32>& OutChoices, const TArray<float>& AccumulateWeights, int32 Count);
	static bool ChoiceByWeights(TArray<int32>& OutChoices, const TArray<float>& Weights, int32 Count);
};
