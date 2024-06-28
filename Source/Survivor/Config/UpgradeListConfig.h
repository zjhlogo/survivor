#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UpgradeListConfig.generated.h"

USTRUCT(BlueprintType)
struct FUpgradeListConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int32 Category;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FString Desc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float Probability;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float Param1;
};
