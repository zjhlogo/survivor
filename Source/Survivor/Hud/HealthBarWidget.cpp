// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

#include "Components/ProgressBar.h"
#include "Survivor/Enemy/EnemyBase.h"

void UHealthBarWidget::BindEvents(AEnemyBase* EnemyActor)
{
	EnemyActor->OnHpChanged.AddUObject(this, &UHealthBarWidget::OnHpChanged);
}

void UHealthBarWidget::OnHpChanged(float CurrHp, float MaxHp)
{
	PbrHealthBar->SetPercent(CurrHp / MaxHp);
}
