// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseAttributeComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FHpChanged, float, float);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVOR_API UBaseAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBaseAttributeComponent();

public:
	FHpChanged OnHpChanged;
};
