#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterLevelConfig.generated.h"

USTRUCT(BlueprintType)
struct FCharacterLevelConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	float BaseHp{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor)
	int32 LevelUpExp{};
};
