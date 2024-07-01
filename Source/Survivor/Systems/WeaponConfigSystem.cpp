// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponConfigSystem.h"
#include "Survivor/Config/Weapon/WeaponTypeConfig.h"
#include "Survivor/Config/Weapon/Weapon100_PistolConfig.h"
#include "Survivor/Config/Weapon/Weapon101_MachineGunConfig.h"
#include "Survivor/Config/Weapon/Weapon200_LaserConfig.h"

UWeaponConfigSystem* UWeaponConfigSystem::Instance = nullptr;

void UWeaponConfigSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Instance = this;
}

void UWeaponConfigSystem::Deinitialize()
{
	Instance = nullptr;
	Super::Deinitialize();
}

const FWeaponTypeConfig* UWeaponConfigSystem::FindWeaponTypeConfig(const FName& TypeId)
{
	return DtWeaponType->FindRow<FWeaponTypeConfig>(TypeId, TEXT("UWeaponConfigSystem"));
}

const FWeapon100_PistolConfig* UWeaponConfigSystem::FindWeapon100_PistolConfig(int32 Level)
{
	return DtWeapon100_Pistol->FindRow<FWeapon100_PistolConfig>(FName(*FString::FromInt(Level)), TEXT("UWeaponConfigSystem"));
}

const FWeapon101_MachineGunConfig* UWeaponConfigSystem::FindWeapon101_MachineGunConfig(int32 Level)
{
	return DtWeapon101_MachineGun->FindRow<FWeapon101_MachineGunConfig>(FName(*FString::FromInt(Level)), TEXT("UWeaponConfigSystem"));
}

const FWeapon200_LaserConfig* UWeaponConfigSystem::FindWeapon200_LaserConfig(int32 Level)
{
	return DtWeapon200_Laser->FindRow<FWeapon200_LaserConfig>(FName(*FString::FromInt(Level)), TEXT("UWeaponConfigSystem"));
}
