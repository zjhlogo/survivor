// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfigSystem.h"

#include "Engine/DataTable.h"
#include "CharacterLevelConfig.h"
#include "DamageTypeConfig.h"
#include "WeaponTypeConfig.h"
#include "WeaponBulletCategoryConfig.h"
#include "WeaponBulletLevelConfig.h"
#include "MonsterConfig.h"
#include "Kismet/GameplayStatics.h"

void UConfigSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UConfigSystem::Deinitialize()
{
	Super::Deinitialize();
}

UConfigSystem* UConfigSystem::Get(const UObject* WorldContextObject)
{
	UConfigSystem* ConfigSystem = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UConfigSystem>();
	check(ConfigSystem)
	return ConfigSystem;
}

const FCharacterLevelConfig* UConfigSystem::FindCharacterLevelConfig(int32 Lv)
{
	return DtCharacterLevel->FindRow<FCharacterLevelConfig>(FName(*FString::FromInt(Lv)), TEXT("Config"));
}

const FDamageTypeConfig* UConfigSystem::FindDamageTypeConfig(int32 TypeId)
{
	return DtDamageType->FindRow<FDamageTypeConfig>(FName(*FString::FromInt(TypeId)), TEXT("Config"));
}

const FWeaponTypeConfig* UConfigSystem::FindWeaponTypeConfig(int32 TypeId)
{
	return DtWeaponType->FindRow<FWeaponTypeConfig>(FName(*FString::FromInt(TypeId)), TEXT("Config"));
}

const FWeaponBulletCategoryConfig* UConfigSystem::FindWeaponBulletCategoryConfig(int32 Category)
{
	return DtWeaponBulletCategory->FindRow<FWeaponBulletCategoryConfig>(FName(*FString::FromInt(Category)), TEXT("Config"));
}

const FWeaponBulletLevelConfig* UConfigSystem::FindWeaponBulletLevelConfig(int32 Category, int32 Lv)
{
	return DtWeaponBulletLevel->FindRow<FWeaponBulletLevelConfig>(FName(*FString::FromInt(Category * 1000 + Lv)), TEXT("Config"));
}

const FMonsterConfig* UConfigSystem::FindMonsterConfig(const FName& Id)
{
	return DtMonster->FindRow<FMonsterConfig>(Id, TEXT("Config"));
}
