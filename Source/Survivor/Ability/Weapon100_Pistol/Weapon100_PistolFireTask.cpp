// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon100_PistolFireTask.h"

#include "AbilitySystemComponent.h"
#include "Weapon100_PistolAttribute.h"
#include "Survivor/Actors/ProjectileBase.h"
#include "Survivor/Config/Weapon/Weapon100_PistolConfig.h"
#include "Survivor/Systems/WeaponConfigSystem.h"

UWeapon100_PistolFireTask::UWeapon100_PistolFireTask()
{
	bTickingTask = true;
}

void UWeapon100_PistolFireTask::Activate()
{
	Super::Activate();

	AbilitySystemComponent->AddSet<UWeapon100_PistolAttribute>();
	UpdateConfig();

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UWeapon100_PistolAttribute::GetLevelAttribute()).
	                        AddLambda([&](const FOnAttributeChangeData& Data)
	                        {
		                        UpdateConfig();
	                        });
}

void UWeapon100_PistolFireTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	ElapseTime += DeltaTime;
	if (WeaponState == ReloadBullet)
	{
		if (ElapseTime >= WeaponConfig->ReloadTime)
		{
			ElapseTime -= WeaponConfig->ReloadTime;
			RemainBulletCount = WeaponConfig->ReloadCount;
			WeaponState = FireBullet;
		}
	}
	else if (WeaponState == FireBullet)
	{
		float OneShootDeltaTime = 1.0f / WeaponConfig->FireFps;
		if (ElapseTime >= OneShootDeltaTime)
		{
			ElapseTime -= OneShootDeltaTime;
			--RemainBulletCount;

			// spawn bullet
			auto Actor = GetAvatarActor();
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.Owner = Actor;
			SpawnParams.Instigator = Cast<APawn>(Actor);
			GetWorld()->SpawnActor<AProjectileBase>(BulletClass, Actor->GetActorTransform(), SpawnParams);

			if (RemainBulletCount <= 0)
			{
				WeaponState = ReloadBullet;
			}
		}
	}
}

void UWeapon100_PistolFireTask::UpdateConfig()
{
	int32 Level = static_cast<int32>(AbilitySystemComponent->GetNumericAttribute(UWeapon100_PistolAttribute::GetLevelAttribute()));
	WeaponConfig = UWeaponConfigSystem::Get().FindWeapon100_PistolConfig(Level);
}
