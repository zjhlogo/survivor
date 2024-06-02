// Copyright Epic Games, Inc. All Rights Reserved.

#include "SurvivorGameMode.h"

#include "EngineUtils.h"
#include "Enemy/EnemyBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "UObject/ConstructorHelpers.h"

ASurvivorGameMode::ASurvivorGameMode()
{
}

void ASurvivorGameMode::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandleSpawn, this, &ASurvivorGameMode::SpawnTimerElapsed, SpawnTimerInterval, true);
}

void ASurvivorGameMode::SpawnTimerElapsed()
{
	// check number of bots
	int NumBots = 0;
	for (TActorIterator<AEnemyBase> It(GetWorld()); It; ++It)
	{
		++NumBots;
		if (NumBots >= MaxEnemy)
		{
			return;
		}
	}

	// run eqs to find a spawn point
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASurvivorGameMode::OnQueryCompleted);
}

void ASurvivorGameMode::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus == EEnvQueryStatus::Type::Success)
	{
		TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
		if (Locations.IsValidIndex(0))
		{
			GetWorld()->SpawnActor<AActor>(EnemyClass, Locations[0], FRotator::ZeroRotator);
		}
	}
}
