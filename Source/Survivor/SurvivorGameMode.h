// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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

protected:
	void SpawnTimerElapsed();

private:
	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	float SpawnTimerInterval{2.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	UEnvQuery* SpawnBotQuery{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemyBase> EnemyClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	int MaxEnemy{10};

private:
	FTimerHandle TimerHandleSpawn;
};
