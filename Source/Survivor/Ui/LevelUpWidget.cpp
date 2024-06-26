// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpWidget.h"

#include "AbilitySystemComponent.h"
#include "Components/Button.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Survivor/Attributes/BulletWeaponAttribute.h"

void ULevelUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameplayStatics::SetGamePaused(this, true);
	BtnChoice0->OnClicked.AddDynamic(this, &ULevelUpWidget::OnButtonClicked);
	BtnChoice1->OnClicked.AddDynamic(this, &ULevelUpWidget::OnButtonClicked);
	BtnChoice2->OnClicked.AddDynamic(this, &ULevelUpWidget::OnButtonClicked);
}

void ULevelUpWidget::NativeDestruct()
{
	UGameplayStatics::SetGamePaused(this, false);
	Super::NativeDestruct();
}

void ULevelUpWidget::SetLevelUpCharacter(ACharacter* Character)
{
	LevelUpCharacter = Character;
}

void ULevelUpWidget::OnButtonClicked()
{
	// TODO: upgrade ability by choice

	auto CharacterAsc = LevelUpCharacter->FindComponentByClass<UAbilitySystemComponent>();
	if (ensure(CharacterAsc))
	{
		auto OldLevel = CharacterAsc->GetNumericAttribute(UBulletWeaponAttribute::GetNumLineAttribute());
		CharacterAsc->SetNumericAttributeBase(UBulletWeaponAttribute::GetNumLineAttribute(), OldLevel + 1);
	}

	RemoveFromParent();
}
