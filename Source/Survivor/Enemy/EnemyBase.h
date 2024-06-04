// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Survivor/Attributes/BaseAttribute.h"
#include "EnemyBase.generated.h"

class UWidgetComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;
class UAbilitySystemComponent;

UCLASS()
class SURVIVOR_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return bIsDead; }

protected:
	virtual void BeginPlay() override;
	virtual void OnHpChanged(const FOnAttributeChangeData& Data);

private:
	// ability system component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystem{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBarWidget{};

	uint8 bIsDead : 1;
};
