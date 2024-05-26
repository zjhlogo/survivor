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

	void SetLaserBeamMaxLength(double MaxLength);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE double GetLaserBeamMaxLength() const { return LaserBeamMaxLength; }

protected:
	virtual void BeginPlay() override;

private:
	uint8 bRotate : 1;
	double OffsetRotation{};
	double RotateSpeed{45.0};
	double LaserBeamMaxLength{300.0};
};
