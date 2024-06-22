// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "Survivor/Config/EnemySpawnInfo.h"
#include "UObject/Object.h"
#include "EnemySpawner.generated.h"

class AEnemyBase;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SURVIVOR_API UEnemySpawner : public UObject
{
	GENERATED_BODY()

public:
	struct FSpawnTracingInfo
	{
		float TimeElapsed;
		int32 CurrEnemyCount;
	};

public:
	void StartPlay();
	void Tick(float DeltaSeconds);

private:
	void EnemyDead(AEnemyBase* EnemyBase);
	void SpawnEnemyByIndex(int32 Index);
	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TArray<FEnemySpawnInfo> SpawnInfos;

	TArray<FSpawnTracingInfo> SpawnTracingInfos;
	TQueue<int32> SpawnQueueIndex;

	UPROPERTY()
	TMap<AEnemyBase*, int32> EnemyMap;
};
