// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBaseAttribute.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"

bool UPawnBaseAttribute::OnPostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHpAttribute())
	{
		SetHp(FMath::Clamp(GetHp(), 0.0f, GetMaxHp()));

		// if not dead
		if ((State & ECharacterState::Dead) == ECharacterState::None)
		{
			// check is dead
			if (GetHp() <= 0.0f)
			{
				State |= ECharacterState::Dead;
				// TODO: notify dead event
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}
