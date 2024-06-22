// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

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

void ULevelUpWidget::OnButtonClicked()
{
	RemoveFromParent();
}
