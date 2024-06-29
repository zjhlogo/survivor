// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpWidget.h"

#include "AbilitySystemComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Survivor/Attributes/WeaponBulletAttribute.h"
#include "Survivor/Attributes/CharacterAttribute.h"
#include "Survivor/Config/UpgradeItemConfig.h"
#include "Survivor/Systems/CharacterUpgradeSystem.h"

void ULevelUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameplayStatics::SetGamePaused(this, true);
	BtnChoice0->OnClicked.AddDynamic(this, &ULevelUpWidget::OnButton0Clicked);
	BtnChoice1->OnClicked.AddDynamic(this, &ULevelUpWidget::OnButton1Clicked);
	BtnChoice2->OnClicked.AddDynamic(this, &ULevelUpWidget::OnButton2Clicked);
}

void ULevelUpWidget::NativeDestruct()
{
	UGameplayStatics::SetGamePaused(this, false);
	Super::NativeDestruct();
}

void ULevelUpWidget::InitView(ACharacter* Character)
{
	LevelUpCharacter = Character;
	UCharacterUpgradeSystem::Get()->RandomChooseItemByWeight(ItemConfigs, 3, LevelUpCharacter);

	TxtChoice0->SetText(FText::FromString(ItemConfigs[0]->Desc));
	TxtChoice1->SetText(FText::FromString(ItemConfigs[1]->Desc));
	TxtChoice2->SetText(FText::FromString(ItemConfigs[2]->Desc));
}

void ULevelUpWidget::OnButtonClicked(int32 Index)
{
	auto CharacterAsc = LevelUpCharacter->FindComponentByClass<UAbilitySystemComponent>();
	check(CharacterAsc);

	const auto* ItemConfig = ItemConfigs[Index];
	check(ItemConfig);

	if (ItemConfig->Category == FName("1000"))
	{
		// upgrade max hp
		CharacterAsc->ApplyModToAttribute(UCharacterAttribute::GetMaxHpAttribute(), EGameplayModOp::Additive, ItemConfig->Param1);
		CharacterAsc->ApplyModToAttribute(UCharacterAttribute::GetHpAttribute(), EGameplayModOp::Additive, ItemConfig->Param1);
	}
	else if (ItemConfig->Category == FName("1010"))
	{
		// upgrade exp factor
		CharacterAsc->ApplyModToAttribute(UCharacterAttribute::GetExpFactorAttribute(), EGameplayModOp::Additive, ItemConfig->Param1);
	}
	else if (ItemConfig->Category == FName("1020"))
	{
		// upgrade moving speed factor
		CharacterAsc->ApplyModToAttribute(UCharacterAttribute::GetMoveSpeedFactorAttribute(), EGameplayModOp::Additive, ItemConfig->Param1);
	}
	else if (ItemConfig->Category == FName("1030"))
	{
		// upgrade pick range
		CharacterAsc->ApplyModToAttribute(UCharacterAttribute::GetPickupRangeFactorAttribute(), EGameplayModOp::Additive, ItemConfig->Param1);
	}
	else if (ItemConfig->Category == FName("1040"))
	{
		// upgrade all damage factor
		CharacterAsc->ApplyModToAttribute(UCharacterAttribute::GetInternalDamageFactorAttribute(), EGameplayModOp::Additive, ItemConfig->Param1);
	}
	else if (ItemConfig->Category == FName("2000"))
	{
		// upgrade bullet damage factor
		CharacterAsc->ApplyModToAttribute(UWeaponBulletAttribute::GetDamageFactorAttribute(), EGameplayModOp::Additive, ItemConfig->Param1);
	}
	else if (ItemConfig->Category == FName("2010"))
	{
		// upgrade bullet number of lines
		CharacterAsc->ApplyModToAttribute(UWeaponBulletAttribute::GetNumLineAttribute(), EGameplayModOp::Additive, ItemConfig->Param1);
	}
	else if (ItemConfig->Category == FName("2020"))
	{
		// TODO: 
	}
	else if (ItemConfig->Category == FName("2030"))
	{
		// TODO: 
	}

	RemoveFromParent();
}
