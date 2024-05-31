// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttribute.h"

#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "../Util/DebugUtil.h"

void UBaseAttribute::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	OnPostGameplayEffectExecute(Data);
}

bool UBaseAttribute::OnPostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHpAttribute())
	{
		SetHp(FMath::Clamp(GetHp(), 0.0f, GetMaxHp()));
		PRINT_R("{0}.Hp={1}", GetOwningActor()->GetActorNameOrLabel(), GetHp());
	}
	else
	{
		return false;
	}

	return true;
}
