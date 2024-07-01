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
	auto AbilitySystemCom = ActorOwner->FindComponentByClass<UAbilitySystemComponent>();
	check(AbilitySystemCom);

	CurrHp = AbilitySystemCom->GetNumericAttribute(UPawnBaseAttribute::GetHpAttribute());
	MaxHp = AbilitySystemCom->GetNumericAttribute(UPawnBaseAttribute::GetMaxHpAttribute());
	CurrExp = AbilitySystemCom->GetNumericAttribute(UCharacterAttribute::GetExpAttribute());
	Level = static_cast<int>(AbilitySystemCom->GetNumericAttribute(UCharacterAttribute::GetLevelAttribute()));
	CurrLevelConfig = UConfigSystem::Get()->FindCharacterLevelConfig(Level);
	UpdateHpView();
	UpdateExpView();
	UpdateLevelView();
	UpdateInfoView();

	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UPawnBaseAttribute::GetHpAttribute()).AddUObject(this, &UIngameHudWidget::OnHpChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UPawnBaseAttribute::GetMaxHpAttribute()).AddUObject(this, &UIngameHudWidget::OnMaxHpChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UCharacterAttribute::GetExpAttribute()).AddUObject(this, &UIngameHudWidget::OnExpChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UCharacterAttribute::GetLevelAttribute()).AddUObject(this, &UIngameHudWidget::OnLevelChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UCharacterAttribute::GetMoveSpeedFactorAttribute()).AddUObject(this,
		&UIngameHudWidget::OnInfoAttributeChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UCharacterAttribute::GetPickupRangeFactorAttribute()).AddUObject(this,
		&UIngameHudWidget::OnInfoAttributeChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UCharacterAttribute::GetExpFactorAttribute()).AddUObject(this,
		&UIngameHudWidget::OnInfoAttributeChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UCharacterAttribute::GetInternalDamageFactorAttribute()).AddUObject(this,
		&UIngameHudWidget::OnInfoAttributeChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UCharacterAttribute::GetExternalDamageFactorAttribute()).AddUObject(this,
		&UIngameHudWidget::OnInfoAttributeChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UCharacterAttribute::GetPhysicsDamageFactorAttribute()).AddUObject(this,
		&UIngameHudWidget::OnInfoAttributeChanged);
	AbilitySystemCom->GetGameplayAttributeValueChangeDelegate(UCharacterAttribute::GetLaserDamageFactorAttribute()).AddUObject(this,
		&UIngameHudWidget::OnInfoAttributeChanged);
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

void UIngameHudWidget::OnInfoAttributeChanged(const FOnAttributeChangeData& Data)
{
	UpdateInfoView();
}

void UIngameHudWidget::UpdateInfoView()
{
	auto Asc = ActorOwner->FindComponentByClass<UAbilitySystemComponent>();
	check(Asc);

	auto MoveSpeedFactor = Asc->GetNumericAttribute(UCharacterAttribute::GetMoveSpeedFactorAttribute());
	TxtSpeedFactor->SetText(FText::Format(NSLOCTEXT("Survivor", "UIngameHudWidget_SpeedFactor", "Speed: {0}%"), MoveSpeedFactor * 100.0f));

	auto PickupRangeFactor = Asc->GetNumericAttribute(UCharacterAttribute::GetPickupRangeFactorAttribute());
	TxtPickupRangeFactor->SetText(FText::Format(NSLOCTEXT("Survivor", "UIngameHudWidget_PickupRangeFactor", "Pickup: {0}%"), PickupRangeFactor * 100.0f));

	auto ExpFactor = Asc->GetNumericAttribute(UCharacterAttribute::GetExpFactorAttribute());
	TxtExpFactor->SetText(FText::Format(NSLOCTEXT("Survivor", "UIngameHudWidget_ExpFactor", "Exp: {0}%"), ExpFactor * 100.0f));

	auto IntDamageFactor = Asc->GetNumericAttribute(UCharacterAttribute::GetInternalDamageFactorAttribute());
	TxtInternalDamageFactor->SetText(FText::Format(NSLOCTEXT("Survivor", "UIngameHudWidget_IntDamageFactor", "Int Damage: {0}%"), IntDamageFactor * 100.0f));

	auto ExtDamageFactor = Asc->GetNumericAttribute(UCharacterAttribute::GetExternalDamageFactorAttribute());
	TxtExternalDamageFactor->SetText(FText::Format(NSLOCTEXT("Survivor", "UIngameHudWidget_ExtDamageFactor", "Ext Damage: {0}%"), ExtDamageFactor * 100.0f));

	auto PhysicsDamageFactor = Asc->GetNumericAttribute(UCharacterAttribute::GetPhysicsDamageFactorAttribute());
	TxtPhysicsDamageFactor->SetText(FText::Format(NSLOCTEXT("Survivor", "UIngameHudWidget_PhysicsDamage", "Physics Damage: {0}%"),
	                                              (1.0f + PhysicsDamageFactor + IntDamageFactor + ExtDamageFactor) * 100.0f));

	auto LaserDamageFactor = Asc->GetNumericAttribute(UCharacterAttribute::GetLaserDamageFactorAttribute());
	TxtLaserDamageFactor->SetText(FText::Format(NSLOCTEXT("Survivor", "UIngameHudWidget_LaserDamage", "Laser Damage: {0}%"),
	                                            (1.0f + LaserDamageFactor + IntDamageFactor + ExtDamageFactor) * 100.0f));
}
