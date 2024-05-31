// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FSurvivorDefine
{
public:
	inline static const FName CollisionProfileCharacter{TEXT("Pawn")};
	inline static const FName CollisionProfileEnemy{TEXT("Enemy")};
	inline static const FName CollisionProfileProjectile{TEXT("Projectile")};
};
