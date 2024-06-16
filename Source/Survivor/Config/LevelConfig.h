#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LevelConfig.generated.h"

USTRUCT(BlueprintType)
struct FLevelConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int32 MaxExp;
};
