// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Survivor/Attributes/BaseAttribute.h"
#include "EnemyBase.generated.h"

class AItemBase;
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

    UFUNCTION(BlueprintImplementableEvent)
    void OnDead();
    
protected:
	virtual void BeginPlay() override;
	virtual void OnHpChanged(const FOnAttributeChangeData& Data);
	virtual void SpawnExp();
	
private:
	// ability system component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystem{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBarWidget{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AItemBase> ExpItemClass;
	
	uint8 bIsDead : 1;
};
