#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponLaserLevelConfig.generated.h"

USTRUCT(BlueprintType)
struct FWeaponLaserLevelConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FName CategoryId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int32 Level{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float BaseDamage{};
};
