// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfigSystem.h"

#include "Engine/DataTable.h"
#include "../Config/CharacterLevelConfig.h"
#include "../Config/DamageTypeConfig.h"
#include "../Config/MonsterConfig.h"
#include "../Config/UpgradeCategoryConfig.h"
#include "../Config/UpgradeItemConfig.h"
#include "UObject/ConstructorHelpers.h"

UConfigSystem* UConfigSystem::Instance = nullptr;

UConfigSystem::UConfigSystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable>
			Asset(TEXT("/Script/Engine.DataTable'/Game/Config/DT_CharacterLevelConfig.DT_CharacterLevelConfig'"));
		DtCharacterLevel = Asset.Object;
	}

	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Config/DT_DamageTypeConfig.DT_DamageTypeConfig'"));
		DtDamageType = Asset.Object;
	}

	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Config/DT_MonsterConfig.DT_MonsterConfig'"));
		DtMonster = Asset.Object;
	}

	{
		static ConstructorHelpers::FObjectFinder<UDataTable>
			Asset(TEXT("/Script/Engine.DataTable'/Game/Config/DT_UpgradeCategoryConfig.DT_UpgradeCategoryConfig'"));
		DtUpgradeCategory = Asset.Object;
	}

	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Config/DT_UpgradeItemConfig.DT_UpgradeItemConfig'"));
		DtUpgradeItem = Asset.Object;
	}
}

void UConfigSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Instance = this;
}

void UConfigSystem::Deinitialize()
{
	Instance = nullptr;
	Super::Deinitialize();
}

const FCharacterLevelConfig* UConfigSystem::FindCharacterLevelConfig(int32 Lv)
{
	return DtCharacterLevel->FindRow<FCharacterLevelConfig>(FName(*FString::FromInt(Lv)), TEXT("Config"));
}

const FDamageTypeConfig* UConfigSystem::FindDamageTypeConfig(int32 TypeId)
{
	return DtDamageType->FindRow<FDamageTypeConfig>(FName(*FString::FromInt(TypeId)), TEXT("Config"));
}

const FMonsterConfig* UConfigSystem::FindMonsterConfig(const FName& Id)
{
	return DtMonster->FindRow<FMonsterConfig>(Id, TEXT("Config"));
}

const FUpgradeCategoryConfig* UConfigSystem::FindUpgradeCategoryConfig(const FName& Id)
{
	return DtUpgradeCategory->FindRow<FUpgradeCategoryConfig>(Id, TEXT("Config"));
}

void UConfigSystem::ForEachUpgradeCategoryConfig(const TFunctionRef<void (const FName& Key, const FUpgradeCategoryConfig& Value)>& Cb)
{
	DtUpgradeCategory->ForeachRow<FUpgradeCategoryConfig>(TEXT("Config"), Cb);
}

const FUpgradeItemConfig* UConfigSystem::FindUpgradeItemConfig(const FName& Id)
{
	return DtUpgradeItem->FindRow<FUpgradeItemConfig>(Id, TEXT("Config"));
}

void UConfigSystem::ForEachUpgradeItemConfig(const TFunctionRef<void(const FName& Key, const FUpgradeItemConfig& Value)>& Cb)
{
	DtUpgradeItem->ForeachRow<FUpgradeItemConfig>(TEXT("Config"), Cb);
}
