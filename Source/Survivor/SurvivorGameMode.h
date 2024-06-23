// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivorGameMode.generated.h"

class UEnemySpawner;

UCLASS(minimalapi)
class ASurvivorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASurvivorGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UEnemySpawner> EnemySpawnerClass;
	TStrongObjectPtr<UEnemySpawner> EnemySpawner{};
};
