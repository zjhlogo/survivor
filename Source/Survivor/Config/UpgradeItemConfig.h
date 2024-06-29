#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UpgradeItemConfig.generated.h"

USTRUCT(BlueprintType)
struct FUpgradeItemConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FName Category;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FString Desc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float Probability{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float Param1{};
};
