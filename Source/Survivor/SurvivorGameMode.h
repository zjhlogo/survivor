// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/EnemySpawnInfo.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivorGameMode.generated.h"

class UEnvQueryInstanceBlueprintWrapper;
class AEnemyBase;
class UEnvQuery;

UCLASS(minimalapi)
class ASurvivorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASurvivorGameMode();

	virtual void StartPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	void SpawnEnemy(const FEnemySpawnInfo& SpawnInfo);

private:
	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TArray<FEnemySpawnInfo> SpawnInfos;

private:
	TArray<float> TimeElapsed;
	TQueue<FEnemySpawnInfo> SpawnQueue;
};
