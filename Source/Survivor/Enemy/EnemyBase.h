// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class UWidgetComponent;
class UBaseAttributeComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;
class UAbilitySystemComponent;

UCLASS()
class SURVIVOR_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	UBaseAttributeComponent* BaseAttributeCom;

	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterDead();

protected:
	virtual void NativeOnCharacterDead();
	
private:
	// ability system component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystem{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBarWidget{};
};
