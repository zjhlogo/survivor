// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttribute.h"
#include "GameplayEffectExtension.h"
#include "Survivor/SurvivorGameMode.h"
#include "Survivor/Config/LevelConfig.h"

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

		ASurvivorGameMode* CurrGameMode = Cast<ASurvivorGameMode>(GetWorld()->GetAuthGameMode());
		check(CurrGameMode);

		// get level config
		if (const FLevelConfig* CurrLevelConfig = CurrGameMode->FindLevelConfig(CurrLevel))
		{
			while (CurrExp >= CurrLevelConfig->MaxExp)
			{
				CurrExp -= CurrLevelConfig->MaxExp;

				// get next level config
				if (const FLevelConfig* NextLevelConfig = CurrGameMode->FindLevelConfig(CurrLevel + 1))
				{
					CurrLevelConfig = NextLevelConfig;
					CurrLevel += 1;
				}
				else
				{
					CurrExp = CurrLevelConfig->MaxExp;
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
