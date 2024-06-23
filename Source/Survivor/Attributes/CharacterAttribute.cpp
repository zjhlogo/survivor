// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttribute.h"
#include "GameplayEffectExtension.h"
#include "Kismet/GameplayStatics.h"
#include "Survivor/Config/ConfigSystem.h"
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

		UConfigSystem* ConfigSystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UConfigSystem>();
		check(ConfigSystem);

		// get level config
		if (const FCharacterLevelConfig* CurrLevelConfig = ConfigSystem->FindCharacterLevelConfig(CurrLevel))
		{
			while (CurrExp >= CurrLevelConfig->LevelUpExp)
			{
				CurrExp -= CurrLevelConfig->LevelUpExp;

				// get next level config
				if (const FCharacterLevelConfig* NextLevelConfig = ConfigSystem->FindCharacterLevelConfig(CurrLevel + 1))
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
