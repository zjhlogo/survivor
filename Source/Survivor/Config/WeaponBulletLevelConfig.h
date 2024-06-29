#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponBulletLevelConfig.generated.h"

USTRUCT(BlueprintType)
struct FWeaponBulletLevelConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int32 CategoryId{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int32 Level{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float BaseDamage{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float BaseCriticalDamage{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float BaseCriticalFactor{};
};
