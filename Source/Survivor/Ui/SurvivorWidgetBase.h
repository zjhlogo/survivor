// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivorWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class SURVIVOR_API USurvivorWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetActorOwner(AActor* Owner);

protected:
	virtual void OnActorOwnerSet();

protected:
	UPROPERTY()
	AActor* ActorOwner{};
};
