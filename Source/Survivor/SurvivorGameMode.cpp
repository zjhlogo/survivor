// Copyright Epic Games, Inc. All Rights Reserved.

#include "SurvivorGameMode.h"
#include "Enemy/EnemySpawner.h"

ASurvivorGameMode::ASurvivorGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASurvivorGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	EnemySpawner.Reset(NewObject<UEnemySpawner>(this, EnemySpawnerClass.Get(), TEXT("EnemySpawner")));
}

void ASurvivorGameMode::StartPlay()
{
	Super::StartPlay();
	EnemySpawner->StartPlay();
}

void ASurvivorGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	EnemySpawner->Tick(DeltaSeconds);
}
