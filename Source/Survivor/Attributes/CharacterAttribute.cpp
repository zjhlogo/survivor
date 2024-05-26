// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttribute.h"

bool UCharacterAttribute::OnPostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Super::OnPostGameplayEffectExecute(Data)) return true;

	return false;
}
