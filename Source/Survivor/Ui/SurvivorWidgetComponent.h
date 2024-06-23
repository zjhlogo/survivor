﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SurvivorWidgetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVOR_API USurvivorWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	USurvivorWidgetComponent();

	virtual void InitWidget() override;
};
