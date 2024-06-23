// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Survivor/Attributes/BaseAttribute.h"
#include "MonsterBase.generated.h"

class USurvivorWidgetComponent;
class AItemBase;
class UWidgetComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;
class UAbilitySystemComponent;
class AMonsterBase;

DECLARE_DELEGATE_OneParam(FOnMonsterDead, AMonsterBase*);

UCLASS()
class SURVIVOR_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMonsterBase();

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return bIsDead; }

	UFUNCTION(BlueprintImplementableEvent)
	void OnDead();

protected:
	virtual void PostInitializeComponents() override;
	virtual void OnHpChanged(const FOnAttributeChangeData& Data);
	virtual void SpawnExp();

	UFUNCTION()
	void OnOverlappedWithCharacter(UPrimitiveComponent* OverlappedComponent,
	                               AActor* OtherActor,
	                               UPrimitiveComponent* OtherComp,
	                               int32 OtherBodyIndex,
	                               bool bFromSweep,
	                               const FHitResult& SweepResult);

public:
	FOnMonsterDead OnMonsterDead;

private:
	// ability system component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystem{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USurvivorWidgetComponent* HealthBarWidget{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	FDataTableRowHandle MonsterConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AItemBase> ExpItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GeCastToCharacter;

	uint8 bIsDead : 1;
};
