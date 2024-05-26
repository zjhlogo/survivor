// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SurvivorDefine.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVOR_API USurvivorDefine : public UObject
{
	GENERATED_BODY()

public:
	inline static const FName CollisionProfileCharacter{TEXT("Pawn")};
	inline static const FName CollisionProfileEnemy{TEXT("Enemy")};
	inline static const FName CollisionProfileProjectile{TEXT("Projectile")};
};
