#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UpgradeCategoryConfig.generated.h"

USTRUCT(BlueprintType)
struct FUpgradeCategoryConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FString Desc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float Probability{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FName ConditionTag;
};
