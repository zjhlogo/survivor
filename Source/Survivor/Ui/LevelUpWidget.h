// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorWidgetBase.h"
#include "LevelUpWidget.generated.h"

class UTextBlock;
struct FUpgradeItemConfig;
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
	void InitView(ACharacter* Character);

private:
	UFUNCTION()
	void OnButton0Clicked() { OnButtonClicked(0); }

	UFUNCTION()
	void OnButton1Clicked() { OnButtonClicked(1); }

	UFUNCTION()
	void OnButton2Clicked() { OnButtonClicked(2); }

	void OnButtonClicked(int32 Index);

private:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	UButton* BtnChoice0;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	UButton* BtnChoice1;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	UButton* BtnChoice2;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* TxtChoice0;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* TxtChoice1;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* TxtChoice2;

	UPROPERTY()
	ACharacter* LevelUpCharacter{};

	TArray<const FUpgradeItemConfig*> ItemConfigs;
};
