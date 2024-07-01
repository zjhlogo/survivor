// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WeaponConfigSystem.generated.h"

struct FWeapon200_LaserConfig;
struct FWeapon101_MachineGunConfig;
struct FWeapon100_PistolConfig;
struct FWeaponTypeConfig;
/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class SURVIVOR_API UWeaponConfigSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	static UWeaponConfigSystem& Get()
	{
		check(Instance);
		return *Instance;
	}

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	const FWeaponTypeConfig* FindWeaponTypeConfig(const FName& TypeId);
	const FWeapon100_PistolConfig* FindWeapon100_PistolConfig(int32 Level);
	const FWeapon101_MachineGunConfig* FindWeapon101_MachineGunConfig(int32 Level);
	const FWeapon200_LaserConfig* FindWeapon200_LaserConfig(int32 Level);

private:
	static UWeaponConfigSystem* Instance;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category=survivor,
		meta=(AllowPrivateAccess = "true", RequiredAssetDataTags="RowStructure=/Script/Survivor.WeaponTypeConfig"))
	TObjectPtr<UDataTable> DtWeaponType;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category=survivor,
		meta=(AllowPrivateAccess = "true", RequiredAssetDataTags="RowStructure=/Script/Survivor.Weapon100_PistolConfig"))
	TObjectPtr<UDataTable> DtWeapon100_Pistol;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category=survivor,
		meta=(AllowPrivateAccess = "true", RequiredAssetDataTags="RowStructure=/Script/Survivor.Weapon101_MachineGunConfig"))
	TObjectPtr<UDataTable> DtWeapon101_MachineGun;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category=survivor,
		meta=(AllowPrivateAccess = "true", RequiredAssetDataTags="RowStructure=/Script/Survivor.Weapon200_LaserConfig"))
	TObjectPtr<UDataTable> DtWeapon200_Laser;
};
