// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBase.h"

#include "AbilitySystemComponent.h"
#include "Survivor/Util/SurvivorDefine.h"

ALaserBase::ALaserBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bRotate = false;
}

void ALaserBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* MyOwner = GetOwner();
	if (!ensure(MyOwner))
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!ensure(World))
	{
		return;
	}

	FVector StartPos = MyOwner->GetActorLocation();

	if (bRotate)
	{
		double ElapseTime = FMath::Fmod(World->GetTimeSeconds(), 360.0);
		double Rotation = RotateSpeed * ElapseTime;

		SetActorLocationAndRotation(StartPos, FRotator(0.0, OffsetRotation + Rotation, 0.0));
	}
	else
	{
		SetActorLocation(StartPos);
	}

	// ray cast to check if hit the target
	FVector EndPos = StartPos + GetActorForwardVector() * LaserBeamMaxLength;
	FHitResult HitResult;
	if (World->LineTraceSingleByProfile(HitResult, StartPos, EndPos, FSurvivorDefine::CollisionProfileProjectile))
	{
		OnLaserHitResult(true, StartPos, HitResult.ImpactPoint);

		// apply ge
		if (UAbilitySystemComponent* Ability = HitResult.GetActor()->FindComponentByClass<UAbilitySystemComponent>())
		{
			Ability->ApplyGameplayEffectToSelf(HitGe.GetDefaultObject(), 0, {});
		}
	}
	else
	{
		OnLaserHitResult(false, StartPos, EndPos);
	}
}

void ALaserBase::SetAutoRotateParameter(bool bRot, double OffsetRot, double RotSpeed)
{
	bRotate = bRot;
	OffsetRotation = OffsetRot;
	RotateSpeed = RotSpeed;
}

void ALaserBase::SetLaserBeamMaxLength(double MaxLength)
{
	LaserBeamMaxLength = MaxLength;
}

// Called when the game starts or when spawned
void ALaserBase::BeginPlay()
{
	Super::BeginPlay();

	SetAutoRotateParameter(bRotate, OffsetRotation, RotateSpeed);
}
