// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameHudWidget.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Survivor/Attributes/CharacterAttribute.h"
#include "Survivor/Config/ConfigSystem.h"
#include "Survivor/Config/CharacterLevelConfig.h"

void UIngameHudWidget::OnActorOwnerSet()
{
	UAbilitySystemComponent* AbilitySystemCom = ActorOwner->FindComponentByClass<UAbilitySystemComponent>();
	check(AbilitySystemCom);

	UConfigSystem* ConfigSystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UConfigSystem>();
	check(ConfigSystem);

	CurrHp = AbilitySystemCom->GetNumericAttribute(UBaseAttribute::GetHpAttribute());
	MaxHp = AbilitySystemCom->GetNumericAttribute(UBaseAttribute::GetMaxHpAttribute());
	CurrExp = AbilitySystemCom->GetNumericAttribute(UCharacterAttribute::GetExpAttribute());
	Level = static_cast<int>(AbilitySystemCom->GetNumericAttribute(UCharacterAttribute::GetLevelAttribute()));
	CurrLevelConfig = ConfigSystem->FindCharacterLevelConfig(Level);
	UpdateHpView();
	UpdateExpView();
	UpdateLevelView();

	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UBaseAttribute::GetHpAttribute()).AddUObject(this, &UIngameHudWidget::OnHpChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UBaseAttribute::GetMaxHpAttribute()).AddUObject(this, &UIngameHudWidget::OnMaxHpChanged);
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
}

void UIngameHudWidget::OnExpChanged(const FOnAttributeChangeData& Data)
{
	CurrExp = Data.NewValue;
	UpdateExpView();
}

void UIngameHudWidget::UpdateExpView()
{
	PbrExp->SetPercent(CurrExp / CurrLevelConfig->LevelUpExp);
}

void UIngameHudWidget::OnLevelChanged(const FOnAttributeChangeData& Data)
{
	Level = Data.NewValue;

	UConfigSystem* ConfigSystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UConfigSystem>();
	check(ConfigSystem);
	CurrLevelConfig = ConfigSystem->FindCharacterLevelConfig(Level);

	UpdateLevelView();
}

void UIngameHudWidget::UpdateLevelView()
{
	TxtLevel->SetText(FText::FromString(FString::Printf(TEXT("%d"), Level)));
}
