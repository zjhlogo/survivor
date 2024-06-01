// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorWidgetBase.h"
#include "HealthBarWidget.generated.h"

class AEnemyBase;
class UBaseAttribute;
class UProgressBar;
/**
 * 
 */
UCLASS()
class SURVIVOR_API UHealthBarWidget : public USurvivorWidgetBase
{
	GENERATED_BODY()

public:
	virtual void OnBindEvent(AActor* OwnerActor) override;

private:
	void OnHpChanged(float CurrHp, float MaxHp);

private:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UProgressBar> PbrHealthBar;
};
