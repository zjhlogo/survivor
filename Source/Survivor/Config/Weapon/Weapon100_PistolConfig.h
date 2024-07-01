#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Weapon100_PistolConfig.generated.h"

USTRUCT(BlueprintType)
struct FWeapon100_PistolConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float ReloadTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int32 ReloadCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float FireFps;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float CriticalDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float CriticalFactor;
};
