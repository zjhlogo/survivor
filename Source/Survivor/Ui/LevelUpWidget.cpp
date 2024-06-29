// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Survivor/Config/UpgradeItemConfig.h"
#include "Survivor/Systems/CharacterUpgradeSystem.h"
#include "Survivor/Util/DebugUtil.h"

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
	// TODO: get upgrade ability by choice
	// auto CharacterAsc = LevelUpCharacter->FindComponentByClass<UAbilitySystemComponent>();
	// if (ensure(CharacterAsc))
	// {
	// 	auto OldLevel = CharacterAsc->GetNumericAttribute(UBulletWeaponAttribute::GetNumLineAttribute());
	// 	CharacterAsc->SetNumericAttributeBase(UBulletWeaponAttribute::GetNumLineAttribute(), OldLevel + 1);
	// }
	PRINT_R("Choose Index: {0}", Index);

	RemoveFromParent();
}
