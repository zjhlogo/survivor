// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorWidgetBase.h"
#include "Survivor/Attributes/BaseAttribute.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class SURVIVOR_API UHealthBarWidget : public USurvivorWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void OnActorOwnerSet() override;
	
private:
	void OnHpChanged(const FOnAttributeChangeData& Data);
	void OnMaxHpChanged(const FOnAttributeChangeData& Data);
	void UpdateHpView();
	
private:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UProgressBar> PbrHealthBar;

	float CurrHp;
	float MaxHp;
};
