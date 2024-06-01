// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

#include "Components/ProgressBar.h"
#include "Survivor/Attributes/BaseAttributeComponent.h"

void UHealthBarWidget::OnBindEvent(AActor* OwnerActor)
{
	Super::OnBindEvent(OwnerActor);

	if (!ensure(OwnerActor))
	{
		return;
	}

	UBaseAttributeComponent* BaseAttributeCom = OwnerActor->FindComponentByClass<UBaseAttributeComponent>();
	if (!ensure(BaseAttributeCom))
	{
		return;
	}

	BaseAttributeCom->OnHpChanged.AddUObject(this, &UHealthBarWidget::OnHpChanged);
}

void UHealthBarWidget::OnHpChanged(float CurrHp, float MaxHp)
{
	PbrHealthBar->SetPercent(CurrHp / MaxHp);
}
