// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class UGameplayEffect;

UCLASS()
class SURVIVOR_API AItemBase : public AActor
{
	GENERATED_BODY()

public:
	AItemBase();

	void FlyToPawn(TObjectPtr<APawn> Pawn);
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlappedWithCharacter(UPrimitiveComponent* OverlappedComponent,
						  AActor* OtherActor,
						  UPrimitiveComponent* OtherComp,
						  int32 OtherBodyIndex,
						  bool bFromSweep,
						  const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> PickedGe;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCurveFloat> FlyingSpeedCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	double MinPickedDist{10.0};

	UPROPERTY()
	TObjectPtr<APawn> PawnCollector;

	float ElapsedTime{};
};
