#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponBulletCategoryConfig.generated.h"

USTRUCT(BlueprintType)
struct FWeaponBulletCategoryConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int32 WeaponType{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float ReloadTime{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int32 MaxReload{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FString Desc;
};
