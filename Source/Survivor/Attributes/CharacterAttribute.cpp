// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttribute.h"
#include "GameplayEffectExtension.h"
#include "Survivor/Systems/ConfigSystem.h"
#include "Survivor/Config/CharacterLevelConfig.h"

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

		// get level config
		if (const FCharacterLevelConfig* CurrLevelConfig = UConfigSystem::Get()->FindCharacterLevelConfig(CurrLevel))
		{
			while (CurrExp >= CurrLevelConfig->LevelUpExp)
			{
				CurrExp -= CurrLevelConfig->LevelUpExp;

				// get next level config
				if (const FCharacterLevelConfig* NextLevelConfig = UConfigSystem::Get()->FindCharacterLevelConfig(CurrLevel + 1))
				{
					CurrLevelConfig = NextLevelConfig;
					CurrLevel += 1;
				}
				else
				{
					CurrExp = CurrLevelConfig->LevelUpExp;
					break;
				}
			}
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
