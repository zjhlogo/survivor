// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Survivor/Ability/SurvivorAbilityTask.h"
#include "Weapon100_PistolFireTask.generated.h"

class AProjectileBase;
struct FWeapon100_PistolConfig;
/**
 * 
 */
UCLASS(Blueprintable)
class SURVIVOR_API UWeapon100_PistolFireTask : public USurvivorAbilityTask
{
	GENERATED_BODY()

	enum EWeaponState
	{
		ReloadBullet,
		FireBullet,
	};

public:
	UWeapon100_PistolFireTask();

	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;

private:
	void UpdateConfig();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> BulletClass;

	EWeaponState WeaponState{ReloadBullet};
	float ElapseTime{};

	int32 WeaponLevel{};
	int32 RemainBulletCount{};
	const FWeapon100_PistolConfig* WeaponConfig{};
};
