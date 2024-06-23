// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorWidgetComponent.h"

#include "SurvivorWidgetBase.h"

USurvivorWidgetComponent::USurvivorWidgetComponent()
{
}

void USurvivorWidgetComponent::InitWidget()
{
	Super::InitWidget();

	auto SurvivorWidget = Cast<USurvivorWidgetBase>(GetWidget());
	check(SurvivorWidget);

	SurvivorWidget->SetActorOwner(GetOwner());
}
