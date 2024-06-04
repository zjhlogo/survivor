// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorWidgetBase.h"
#include "Survivor/Attributes/BaseAttribute.h"
#include "IngameHudWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SURVIVOR_API UIngameHudWidget : public USurvivorWidgetBase
{
	GENERATED_BODY()

public:
	virtual void OnBindEvent(AActor* OwnerActor) override;

private:
	void OnHpChanged(const FOnAttributeChangeData& Data);
	void OnMaxHpChanged(const FOnAttributeChangeData& Data);
	void UpdateHpView();

	void OnExpChanged(const FOnAttributeChangeData& Data);
	void UpdateExpView();
	void OnLevelChanged(const FOnAttributeChangeData& Data);
	void UpdateLevelView();

private:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	UProgressBar* PbrHp;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	UProgressBar* PbrExp;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* TxtLevel;

	float CurrHp;
	float MaxHp;

	float CurrExp;
	int Level;

};
