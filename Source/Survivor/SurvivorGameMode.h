// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivorGameMode.generated.h"

class UEnemySpawner;
struct FLevelConfig;
class UDataTable;

UCLASS(minimalapi)
class ASurvivorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASurvivorGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	const FLevelConfig* FindLevelConfig(int Lv);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UEnemySpawner> EnemySpawnerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	UDataTable* DtLevelConfig{};

	TStrongObjectPtr<UEnemySpawner> EnemySpawner{};
};
