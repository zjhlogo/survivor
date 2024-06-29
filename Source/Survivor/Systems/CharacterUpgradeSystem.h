// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Survivor/Config/UpgradeCategoryConfig.h"
#include "CharacterUpgradeSystem.generated.h"

struct FUpgradeItemConfig;
struct FUpgradeCategoryConfig;
/**
 * 
 */
UCLASS()
class SURVIVOR_API UCharacterUpgradeSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	struct FUpgradeItemGroup
	{
		FUpgradeItemGroup(const FName& InCategoryKey, const TArray<FName>& InItemKeys, const TArray<float>& InAccumulateWeights)
		{
			CategoryKey = InCategoryKey;
			ItemKeys = InItemKeys;
			AccumulateWeights = InAccumulateWeights;
		}

		FName CategoryKey;
		TArray<FName> ItemKeys;
		TArray<float> AccumulateWeights;
	};

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	FORCEINLINE static UCharacterUpgradeSystem* Get() { return Instance; }

	bool RandomChooseUpgradableCategories(TArray<FName>& OutCategories, int32 MaxCategories, ACharacter* Character);
	bool RandomChooseItemByWeight(TArray<const FUpgradeItemConfig*>& OutItems, const TArray<FName>& InCategories);
	bool RandomChooseItemByWeight(TArray<const FUpgradeItemConfig*>& OutItems, int32 MaxCategories, ACharacter* Character);

private:
	static UCharacterUpgradeSystem* Instance;

	TMap<FName, FUpgradeItemGroup> UpgradeItemGroupMap;
};
