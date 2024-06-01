// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class AEnemyBase;
class UBaseAttribute;
class UProgressBar;
/**
 * 
 */
UCLASS()
class SURVIVOR_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindEvents(AEnemyBase* EnemyActor);

private:
	void OnHpChanged(float CurrHp, float MaxHp);

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UProgressBar> PbrHealthBar;
};
