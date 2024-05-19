// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBase.h"

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

	FVector Pos = MyOwner->GetActorLocation();

	if (bRotate)
	{
		UWorld* World = GetWorld();
		if (!ensure(World))
		{
			return;
		}

		double ElapseTime = FMath::Fmod(World->GetTimeSeconds(), 360.0);
		double Rotation = RotateSpeed * ElapseTime;

		SetActorLocationAndRotation(Pos, FRotator(0.0, OffsetRotation + Rotation, 0.0));
	}
	else
	{
		SetActorLocation(Pos);
	}
}

void ALaserBase::SetAutoRotateParameter(bool bRot, double OffsetRot, double RotSpeed)
{
	bRotate = bRot;
	OffsetRotation = OffsetRot;
	RotateSpeed = RotSpeed;
}

// Called when the game starts or when spawned
void ALaserBase::BeginPlay()
{
	Super::BeginPlay();

	SetAutoRotateParameter(bRotate, OffsetRotation, RotateSpeed);
}
