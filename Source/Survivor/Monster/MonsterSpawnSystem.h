// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "UObject/Object.h"
#include "MonsterSpawnSystem.generated.h"

class AMonsterBase;

class UEnvQuery;

USTRUCT(BlueprintType)
struct FMonsterSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float SpawnTimerInterval{2.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	UEnvQuery* SpawnBotQuery{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	TSubclassOf<AMonsterBase> MonsterClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int MaxNumMonster{10};
};

USTRUCT()
struct FMonsterSpawnTracing
{
	GENERATED_BODY()

	float TimeElapsed;
	int32 CurrCount;
};

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class SURVIVOR_API UMonsterSpawnSystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UMonsterSpawnSystem, STATGROUP_Tickables); }

private:
	void OnMonsterDead(AMonsterBase* MonsterBase);
	void SpawnEnemyByIndex(int32 Index);
	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TArray<FMonsterSpawnInfo> MonsterSpawnInfos;

	TArray<FMonsterSpawnTracing> MonsterSpawnTracings;
	TQueue<int32> SpawnQueueIndex;

	UPROPERTY()
	TMap<AMonsterBase*, int32> MonsterMap;
};
