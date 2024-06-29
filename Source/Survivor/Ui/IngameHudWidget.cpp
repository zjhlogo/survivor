// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameHudWidget.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Survivor/Attributes/CharacterAttribute.h"
#include "Survivor/Systems/ConfigSystem.h"
#include "Survivor/Config/CharacterLevelConfig.h"

void UIngameHudWidget::OnActorOwnerSet()
{
	UAbilitySystemComponent* AbilitySystemCom = ActorOwner->FindComponentByClass<UAbilitySystemComponent>();
	check(AbilitySystemCom);

	CurrHp = AbilitySystemCom->GetNumericAttribute(UPawnBaseAttribute::GetHpAttribute());
	MaxHp = AbilitySystemCom->GetNumericAttribute(UPawnBaseAttribute::GetMaxHpAttribute());
	CurrExp = AbilitySystemCom->GetNumericAttribute(UCharacterAttribute::GetExpAttribute());
	Level = static_cast<int>(AbilitySystemCom->GetNumericAttribute(UCharacterAttribute::GetLevelAttribute()));
	CurrLevelConfig = UConfigSystem::Get()->FindCharacterLevelConfig(Level);
	UpdateHpView();
	UpdateExpView();
	UpdateLevelView();

	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UPawnBaseAttribute::GetHpAttribute()).AddUObject(this, &UIngameHudWidget::OnHpChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UPawnBaseAttribute::GetMaxHpAttribute()).AddUObject(this, &UIngameHudWidget::OnMaxHpChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UCharacterAttribute::GetExpAttribute()).AddUObject(this, &UIngameHudWidget::OnExpChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UCharacterAttribute::GetLevelAttribute()).AddUObject(this, &UIngameHudWidget::OnLevelChanged);
}

void UIngameHudWidget::OnHpChanged(const FOnAttributeChangeData& Data)
{
	CurrHp = Data.NewValue;
	UpdateHpView();
}

void UIngameHudWidget::OnMaxHpChanged(const FOnAttributeChangeData& Data)
{
	MaxHp = Data.NewValue;
	UpdateHpView();
}

void UIngameHudWidget::UpdateHpView()
{
	PbrHp->SetPercent(CurrHp / MaxHp);
	TxtHp->SetText(FText::Format(NSLOCTEXT("Survivor", "UIngameHudWidget_Hp", "{0}/{1}"), CurrHp, MaxHp));
}

void UIngameHudWidget::OnExpChanged(const FOnAttributeChangeData& Data)
{
	CurrExp = Data.NewValue;
	UpdateExpView();
}

void UIngameHudWidget::UpdateExpView()
{
	PbrExp->SetPercent(CurrExp / CurrLevelConfig->LevelUpExp);
	TxtExp->SetText(FText::Format(NSLOCTEXT("Survivor", "UIngameHudWidget_Exp", "{0}/{1}"), CurrExp, CurrLevelConfig->LevelUpExp));
}

void UIngameHudWidget::OnLevelChanged(const FOnAttributeChangeData& Data)
{
	Level = Data.NewValue;

	CurrLevelConfig = UConfigSystem::Get()->FindCharacterLevelConfig(Level);

	UpdateLevelView();
}

void UIngameHudWidget::UpdateLevelView()
{
	TxtLevel->SetText(FText::FromString(FString::Printf(TEXT("%d"), Level)));
}
