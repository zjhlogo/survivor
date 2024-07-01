// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterUpgradeSystem.h"

#include "AbilitySystemComponent.h"
#include "ConfigSystem.h"
#include "GameFramework/Character.h"
#include "Survivor/Config/UpgradeItemConfig.h"
#include "Survivor/Util/SurvivorDefine.h"

UCharacterUpgradeSystem* UCharacterUpgradeSystem::Instance = nullptr;

void UCharacterUpgradeSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Collection.InitializeDependency(UConfigSystem::StaticClass());

	UConfigSystem::Get()->ForEachUpgradeItemConfig([&](const FName& Key, const FUpgradeItemConfig& Value)
	{
		auto UpgradeItemGroup = UpgradeItemGroupMap.Find(Value.Category);
		if (UpgradeItemGroup == nullptr)
		{
			UpgradeItemGroupMap.Emplace(Value.Category, FUpgradeItemGroup(Value.Category, {Key}, {Value.Probability}));
		}
		else
		{
			UpgradeItemGroup->ItemKeys.Emplace(Key);
			UpgradeItemGroup->AccumulateWeights.Emplace(UpgradeItemGroup->AccumulateWeights.Last() + Value.Probability);
		}
	});

	Instance = this;
}

void UCharacterUpgradeSystem::Deinitialize()
{
	Instance = nullptr;
	Super::Deinitialize();
}

bool UCharacterUpgradeSystem::RandomChooseUpgradableCategories(TArray<FName>& OutCategories, int32 MaxCategories, ACharacter* Character)
{
	auto CharacterAsc = Character->FindComponentByClass<UAbilitySystemComponent>();

	// get all available categories
	TArray<FName> AvailableCategories;
	TArray<float> AccumulateWeights;
	float TotalWeight = 0.0f;
	UConfigSystem::Get()->ForEachUpgradeCategoryConfig([&](const FName& Key, const FUpgradeCategoryConfig& Value)
	{
		if (Value.ConditionTag.IsNone() || CharacterAsc->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(Value.ConditionTag)))
		{
			AvailableCategories.Add(Key);

			TotalWeight += Value.Probability;
			AccumulateWeights.Add(TotalWeight);
		}
	});

	// random choose category by weight OutCategories
	TSet<int32> Choices;
	for (int i = 0; i < 100; ++i)
	{
		auto Index = FSurvivorDefine::ChoiceByAccumulateWeights(AccumulateWeights);
		if (Choices.Contains(Index))
		{
			continue;
		}
		Choices.Add(Index);
		if (Choices.Num() >= MaxCategories)
		{
			break;
		}
	}

	OutCategories.Empty();
	for (const auto& Choice : Choices)
	{
		OutCategories.Add(AvailableCategories[Choice]);
	}

	return true;
}

bool UCharacterUpgradeSystem::RandomChooseItemByWeight(TArray<const FUpgradeItemConfig*>& OutItems, const TArray<FName>& InCategories)
{
	for (const auto& CategoryKey : InCategories)
	{
		const FUpgradeItemGroup* UpgradeItemGroup = UpgradeItemGroupMap.Find(CategoryKey);
		check(UpgradeItemGroup);

		int32 Index = FSurvivorDefine::ChoiceByAccumulateWeights(UpgradeItemGroup->AccumulateWeights);
		const FName& ItemKey = UpgradeItemGroup->ItemKeys[Index];
		const FUpgradeItemConfig* ItemConfig = UConfigSystem::Get()->FindUpgradeItemConfig(ItemKey);
		check(ItemConfig);
		OutItems.Emplace(ItemConfig);
	}

	return true;
}

bool UCharacterUpgradeSystem::RandomChooseItemByWeight(TArray<const FUpgradeItemConfig*>& OutItems, int32 MaxCategories, ACharacter* Character)
{
	TArray<FName> CategoryConfigs;
	RandomChooseUpgradableCategories(CategoryConfigs, MaxCategories, Character);

	return RandomChooseItemByWeight(OutItems, CategoryConfigs);
}
