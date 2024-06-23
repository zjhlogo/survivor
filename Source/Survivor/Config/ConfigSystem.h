// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ConfigSystem.generated.h"

struct FWeaponBulletLevelConfig;
struct FWeaponBulletCategoryConfig;
struct FWeaponTypeConfig;
struct FDamageTypeConfig;
struct FCharacterLevelConfig;
class UDataTable;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class SURVIVOR_API UConfigSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	const FCharacterLevelConfig* FindCharacterLevelConfig(int32 Lv);
	const FDamageTypeConfig* FindDamageTypeConfig(int32 TypeId);
	const FWeaponTypeConfig* FindWeaponTypeConfig(int32 TypeId);
	const FWeaponBulletCategoryConfig* FindWeaponBulletCategoryConfig(int32 Category);
	const FWeaponBulletLevelConfig* FindWeaponBulletLevelConfig(int32 Category, int32 Lv);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	UDataTable* DtCharacterLevel{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	UDataTable* DtDamageType{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	UDataTable* DtWeaponType{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	UDataTable* DtWeaponBulletCategory{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	UDataTable* DtWeaponBulletLevel{};
};
