// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "EnemyBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"

void UEnemySpawner::EnemyDead(AEnemyBase* EnemyBase)
{
	if (const int32* IndexPtr = EnemyMap.Find(EnemyBase))
	{
		EnemyMap.Remove(EnemyBase);
		SpawnTracingInfos[*IndexPtr].CurrEnemyCount--;
	}
}

void UEnemySpawner::StartPlay()
{
	auto Num = SpawnInfos.Num();
	SpawnTracingInfos.SetNum(Num);
	for (int i = 0; i < Num; ++i)
	{
		SpawnTracingInfos[i] = FSpawnTracingInfo({SpawnInfos[i].SpawnTimerInterval, 0});
	}
}

void UEnemySpawner::Tick(float DeltaSeconds)
{
	for (int i = 0; i < SpawnInfos.Num(); ++i)
	{
		if (SpawnTracingInfos[i].CurrEnemyCount >= SpawnInfos[i].MaxEnemy)
		{
			continue;
		}

		SpawnTracingInfos[i].TimeElapsed += DeltaSeconds;
		if (SpawnTracingInfos[i].TimeElapsed < SpawnInfos[i].SpawnTimerInterval)
		{
			continue;
		}

		SpawnTracingInfos[i].TimeElapsed -= SpawnInfos[i].SpawnTimerInterval;
		SpawnEnemyByIndex(i);
	}
}

void UEnemySpawner::SpawnEnemyByIndex(int32 Index)
{
	SpawnQueueIndex.Enqueue(Index);

	// run eqs to find a spawn point
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this,
	                                                                                 SpawnInfos[Index].SpawnBotQuery,
	                                                                                 this,
	                                                                                 EEnvQueryRunMode::RandomBest5Pct,
	                                                                                 nullptr);
	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &UEnemySpawner::OnQueryCompleted);
}

void UEnemySpawner::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	int32 Index;
	ensure(SpawnQueueIndex.Dequeue(Index));

	if (QueryStatus == EEnvQueryStatus::Type::Success)
	{
		TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
		if (Locations.IsValidIndex(0))
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AActor* Actor = GetWorld()->SpawnActor<AActor>(SpawnInfos[Index].EnemyClass, Locations[0], FRotator::ZeroRotator, SpawnParams);

			AEnemyBase* EnemyBase = Cast<AEnemyBase>(Actor);
			check(EnemyBase);
			EnemyBase->OnEnemyDead.BindUObject(this, &UEnemySpawner::EnemyDead);

			EnemyMap.Emplace(EnemyBase, Index);
			SpawnTracingInfos[Index].CurrEnemyCount++;
		}
	}
}
