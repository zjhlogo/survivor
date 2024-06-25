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

	static bool IsGameRunning();
};
