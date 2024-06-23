// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

#include "Components/ProgressBar.h"

void UHealthBarWidget::OnActorOwnerSet()
{
	UAbilitySystemComponent* AbilitySystemCom = ActorOwner->FindComponentByClass<UAbilitySystemComponent>();
	if (!ensure(AbilitySystemCom))
	{
		return;
	}

	CurrHp = AbilitySystemCom->GetNumericAttribute(UBaseAttribute::GetHpAttribute());
	MaxHp = AbilitySystemCom->GetNumericAttribute(UBaseAttribute::GetMaxHpAttribute());
	UpdateHpView();

	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UBaseAttribute::GetHpAttribute()).AddUObject(this, &UHealthBarWidget::OnHpChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UBaseAttribute::GetMaxHpAttribute()).AddUObject(this, &UHealthBarWidget::OnMaxHpChanged);
}

void UHealthBarWidget::OnHpChanged(const FOnAttributeChangeData& Data)
{
	CurrHp = Data.NewValue;
	UpdateHpView();
}

void UHealthBarWidget::OnMaxHpChanged(const FOnAttributeChangeData& Data)
{
	MaxHp = Data.NewValue;
	UpdateHpView();
}

void UHealthBarWidget::UpdateHpView()
{
	PbrHealthBar->SetPercent(CurrHp / MaxHp);
}
