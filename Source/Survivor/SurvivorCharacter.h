// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivorCharacter.generated.h"

class USurvivorBaseAbility;
class UGameplayAbility;
class UAbilitySystemComponent;

UCLASS(Blueprintable)
class ASurvivorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASurvivorCharacter();

	virtual void BeginPlay() override;
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent sub-object **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom sub-object **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// ability system component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystem;

	// default abilities on birth
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = survivor, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<USurvivorBaseAbility>> GainAbilitiesOnBirth;
};
