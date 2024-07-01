#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponTypeConfig.generated.h"

USTRUCT(BlueprintType)
struct FWeaponTypeConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int32 DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FString Desc;
};
