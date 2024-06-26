// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorWidgetBase.h"
#include "LevelUpWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SURVIVOR_API ULevelUpWidget : public USurvivorWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	void SetLevelUpCharacter(ACharacter* Character);

private:
	UFUNCTION()
	void OnButtonClicked();
	
private:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	UButton* BtnChoice0;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	UButton* BtnChoice1;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	UButton* BtnChoice2;

	UPROPERTY()
	ACharacter* LevelUpCharacter{};
};
