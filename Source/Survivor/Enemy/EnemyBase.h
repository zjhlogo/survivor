// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.generated.h"

class UWidgetComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;
class UAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_TwoParams(FHpChanged, float, float);

UCLASS()
class SURVIVOR_API AEnemyBase : public AActor
{
	GENERATED_BODY()

public:
	AEnemyBase();
	virtual void Tick(float DeltaTime) override;

	UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem; }

	FHpChanged OnHpChanged;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* Collision{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh{};

	// ability system component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystem{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBar{};
};
