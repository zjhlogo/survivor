#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DamageTypeConfig.generated.h"

USTRUCT(BlueprintType)
struct FDamageTypeConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FString Desc;
};
