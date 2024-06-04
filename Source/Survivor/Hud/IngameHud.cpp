// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameHud.h"

#include "SurvivorWidgetBase.h"

void AIngameHud::BeginPlay()
{
	Super::BeginPlay();

	USurvivorWidgetBase* Widget = CreateWidget<USurvivorWidgetBase>(GetWorld(), HudWidget);
	Widget->AddToViewport();
	Widget->OnBindEvent(GetOwningPlayerController()->GetPawn());
}
