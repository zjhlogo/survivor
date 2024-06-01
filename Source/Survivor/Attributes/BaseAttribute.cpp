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

		AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		UBaseAttributeComponent* BaseAttributeCom = TargetActor->FindComponentByClass<UBaseAttributeComponent>();
		if (ensure(BaseAttributeCom))
		{
			BaseAttributeCom->OnHpChanged.Broadcast(GetHp(), GetMaxHp());
		}
	}
	else
	{
		return false;
	}

	return true;
}
