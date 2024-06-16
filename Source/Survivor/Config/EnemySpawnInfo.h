#pragma once

#include "CoreMinimal.h"
#include "EnemySpawnInfo.generated.h"

class AEnemyBase;
class UEnvQuery;

USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float SpawnTimerInterval{2.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	UEnvQuery* SpawnBotQuery{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	TSubclassOf<AEnemyBase> EnemyClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int MaxEnemy{10};
};
