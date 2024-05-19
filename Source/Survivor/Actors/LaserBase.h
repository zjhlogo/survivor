// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserBase.generated.h"

UCLASS()
class SURVIVOR_API ALaserBase : public AActor
{
	GENERATED_BODY()

public:
	ALaserBase();
	virtual void Tick(float DeltaTime) override;

	void SetAutoRotateParameter(bool bRot, double OffsetRot, double RotSpeed);

protected:
	virtual void BeginPlay() override;

private:
	uint8 bRotate : 1;
	double OffsetRotation{};
	double RotateSpeed{45.0};
};
