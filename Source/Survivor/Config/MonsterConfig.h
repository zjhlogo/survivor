#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MonsterConfig.generated.h"

USTRUCT(BlueprintType)
struct FMonsterConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	FString Desc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float BaseHp{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float BaseDamage{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int32 Ai{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float DropExp{};
};
