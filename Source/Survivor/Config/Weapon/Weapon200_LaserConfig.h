#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Weapon200_LaserConfig.generated.h"

USTRUCT(BlueprintType)
struct FWeapon200_LaserConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float ReloadTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float Duration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float Damage;
};
