﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ConfigSystem.generated.h"

struct FWeaponLaserLevelConfig;
struct FWeaponLaserCategoryConfig;
struct FUpgradeItemConfig;
struct FUpgradeCategoryConfig;
struct FMonsterConfig;
struct FWeaponBulletLevelConfig;
struct FWeaponBulletCategoryConfig;
struct FWeaponTypeConfig;
struct FDamageTypeConfig;
struct FCharacterLevelConfig;
class UDataTable;
/**
 * 
 */
UCLASS()
class SURVIVOR_API UConfigSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UConfigSystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	FORCEINLINE static UConfigSystem* Get() { return Instance; }

	const FCharacterLevelConfig* FindCharacterLevelConfig(int32 Lv);
	const FDamageTypeConfig* FindDamageTypeConfig(int32 TypeId);
	const FWeaponTypeConfig* FindWeaponTypeConfig(int32 TypeId);
	const FWeaponBulletCategoryConfig* FindWeaponBulletCategoryConfig(const FName& CategoryId);
	const FWeaponBulletLevelConfig* FindWeaponBulletLevelConfig(int32 Category, int32 Lv);
	const FWeaponLaserCategoryConfig* FindWeaponLaserCategoryConfig(const FName& CategoryId);
	const FWeaponLaserLevelConfig* FindWeaponLaserLevelConfig(int32 Category, int32 Lv);
	const FMonsterConfig* FindMonsterConfig(const FName& Id);

	const FUpgradeCategoryConfig* FindUpgradeCategoryConfig(const FName& Id);
	void ForEachUpgradeCategoryConfig(const TFunctionRef<void (const FName& Key, const FUpgradeCategoryConfig& Value)>& Cb);

	const FUpgradeItemConfig* FindUpgradeItemConfig(const FName& Id);
	void ForEachUpgradeItemConfig(const TFunctionRef<void (const FName& Key, const FUpgradeItemConfig& Value)>& Cb);

private:
	UPROPERTY()
	UDataTable* DtCharacterLevel{};

	UPROPERTY()
	UDataTable* DtDamageType{};

	UPROPERTY()
	UDataTable* DtWeaponType{};

	UPROPERTY()
	UDataTable* DtWeaponBulletCategory{};
	UPROPERTY()
	UDataTable* DtWeaponBulletLevel{};

	UPROPERTY()
	UDataTable* DtWeaponLaserCategory{};
	UPROPERTY()
	UDataTable* DtWeaponLaserLevel{};

	UPROPERTY()
	UDataTable* DtMonster{};

	UPROPERTY()
	UDataTable* DtUpgradeCategory{};

	UPROPERTY()
	UDataTable* DtUpgradeItem{};

	static UConfigSystem* Instance;
};
