// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttribute.h"
#include "GameplayEffectExtension.h"

bool UCharacterAttribute::OnPostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Super::OnPostGameplayEffectExecute(Data))
	{
		return true;
	}

	if (Data.EvaluatedData.Attribute == GetExpAttribute())
	{
		float CurrExp = GetExp();
		float CurrLevel = GetLevel();
		// TODO: get max exp from level
		float MaxExp = CurrLevel * 100.0f;

		while (CurrExp >= MaxExp)
		{
			CurrExp -= MaxExp;
			CurrLevel += 1;
			// TODO: get max exp from level
			MaxExp = CurrLevel * 100.0f;
		}

		SetExp(CurrExp);

		// notify level changed
		if (CurrLevel != GetLevel())
		{
			SetLevel(CurrLevel);
		}
	}

	return false;
}
