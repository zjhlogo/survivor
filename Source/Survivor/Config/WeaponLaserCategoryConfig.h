#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponLaserCategoryConfig.generated.h"

USTRUCT(BlueprintType)
struct FWeaponLaserCategoryConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float ReloadTime{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FString Desc;
};
