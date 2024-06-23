// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnSystem.h"
#include "MonsterBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"

void UMonsterSpawnSystem::OnMonsterDead(AMonsterBase* MonsterBase)
{
	if (const int32* IndexPtr = MonsterMap.Find(MonsterBase))
	{
		MonsterMap.Remove(MonsterBase);
		MonsterSpawnTracings[*IndexPtr].CurrCount--;
	}
}

void UMonsterSpawnSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	auto Num = MonsterSpawnInfos.Num();
	MonsterSpawnTracings.SetNum(Num);
	for (int i = 0; i < Num; ++i)
	{
		MonsterSpawnTracings[i] = FMonsterSpawnTracing({MonsterSpawnInfos[i].SpawnTimerInterval, 0});
	}
}

void UMonsterSpawnSystem::Deinitialize()
{
	// TODO: 
	Super::Deinitialize();
}

void UMonsterSpawnSystem::Tick(float DeltaTime)
{
	for (int i = 0; i < MonsterSpawnInfos.Num(); ++i)
	{
		if (MonsterSpawnTracings[i].CurrCount >= MonsterSpawnInfos[i].MaxNumMonster)
		{
			continue;
		}

		MonsterSpawnTracings[i].TimeElapsed += DeltaTime;
		if (MonsterSpawnTracings[i].TimeElapsed < MonsterSpawnInfos[i].SpawnTimerInterval)
		{
			continue;
		}

		MonsterSpawnTracings[i].TimeElapsed -= MonsterSpawnInfos[i].SpawnTimerInterval;
		SpawnEnemyByIndex(i);
	}
}

void UMonsterSpawnSystem::SpawnEnemyByIndex(int32 Index)
{
	SpawnQueueIndex.Enqueue(Index);

	// run eqs to find a spawn point
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this,
	                                                                                 MonsterSpawnInfos[Index].SpawnBotQuery,
	                                                                                 this,
	                                                                                 EEnvQueryRunMode::RandomBest5Pct,
	                                                                                 nullptr);
	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &UMonsterSpawnSystem::OnQueryCompleted);
}

void UMonsterSpawnSystem::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
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
			AActor* Actor = GetWorld()->SpawnActor<AActor>(MonsterSpawnInfos[Index].MonsterClass, Locations[0], FRotator::ZeroRotator, SpawnParams);

			AMonsterBase* MonsterBase = Cast<AMonsterBase>(Actor);
			check(MonsterBase);
			MonsterBase->OnMonsterDead.BindUObject(this, &UMonsterSpawnSystem::OnMonsterDead);

			MonsterMap.Emplace(MonsterBase, Index);
			MonsterSpawnTracings[Index].CurrCount++;
		}
	}
}
