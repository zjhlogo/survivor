// Copyright Epic Games, Inc. All Rights Reserved.

#include "SurvivorGameMode.h"

#include "EngineUtils.h"
#include "Enemy/EnemyBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"

ASurvivorGameMode::ASurvivorGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASurvivorGameMode::StartPlay()
{
	Super::StartPlay();

	for (int i = 0; i < SpawnInfos.Num(); ++i)
	{
		TimeElapsed.Add(SpawnInfos[i].SpawnTimerInterval);
	}
}

void ASurvivorGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (int i = 0; i < SpawnInfos.Num(); ++i)
	{
		TimeElapsed[i] += DeltaSeconds;
		if (TimeElapsed[i] >= SpawnInfos[i].SpawnTimerInterval)
		{
			TimeElapsed[i] -= SpawnInfos[i].SpawnTimerInterval;
			SpawnEnemy(SpawnInfos[i]);
		}
	}
}

void ASurvivorGameMode::SpawnEnemy(const FEnemySpawnInfo& SpawnInfo)
{
	// check number of bots
	int NumBots = 0;
	for (TActorIterator<AEnemyBase> It(GetWorld()); It; ++It)
	{
		++NumBots;
		if (NumBots >= SpawnInfo.MaxEnemy)
		{
			return;
		}
	}

	SpawnQueue.Enqueue(SpawnInfo);

	// run eqs to find a spawn point
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this,
	                                                                                 SpawnInfo.SpawnBotQuery,
	                                                                                 this,
	                                                                                 EEnvQueryRunMode::RandomBest5Pct,
	                                                                                 nullptr);
	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASurvivorGameMode::OnQueryCompleted);
}

void ASurvivorGameMode::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	FEnemySpawnInfo SpawnInfo;
	if (!SpawnQueue.Dequeue(SpawnInfo))
	{
		return;
	}

	if (QueryStatus == EEnvQueryStatus::Type::Success)
	{
		TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
		if (Locations.IsValidIndex(0))
		{
			GetWorld()->SpawnActor<AActor>(SpawnInfo.EnemyClass, Locations[0], FRotator::ZeroRotator);
		}
	}
}
