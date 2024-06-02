// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttribute.h"

#include "BaseAttributeComponent.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"

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

		// if not dead
		if ((State & ECharacterState::Dead) == ECharacterState::None)
		{
			// notify hp changed event
			AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
			UBaseAttributeComponent* BaseAttributeCom = TargetActor->FindComponentByClass<UBaseAttributeComponent>();
			if (ensure(BaseAttributeCom))
			{
				BaseAttributeCom->OnHpChanged.Broadcast(GetHp(), GetMaxHp());
			}

			// check is dead
			if (GetHp() <= 0.0f)
			{
				State |= ECharacterState::Dead;
				// notify dead event
				BaseAttributeCom->OnCharacterDead.Broadcast();
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}
