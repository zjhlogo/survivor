// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivorCharacter.generated.h"

struct FOnAttributeChangeData;
class USphereComponent;
class USurvivorBaseAbility;
class UGameplayAbility;
class UAbilitySystemComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS(Blueprintable)
class ASurvivorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASurvivorCharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent sub-object **/
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom sub-object **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystem; }

protected:
	void OnHpChanged(const FOnAttributeChangeData& Data);
	void OnLevelUp(const FOnAttributeChangeData& Data);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnDead();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLevelUp();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent{};

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom{};

	// item picker
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character, meta=(AllowPrivateAccess = "true"))
	USphereComponent* ItemPicker{};

	// ability system component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character, meta=(AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystem{};

	// default abilities on birth
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TArray<TSubclassOf<USurvivorBaseAbility>> GainAbilitiesOnBirth;
	
	uint8 bIsDead : 1;
};
