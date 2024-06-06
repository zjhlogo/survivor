// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IngameHud.generated.h"

class USurvivorWidgetBase;

/**
 * 
 */
UCLASS()
class SURVIVOR_API AIngameHud : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=survivor, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<USurvivorWidgetBase> HudWidget;
};
