// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttribute.h"

#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "../Util/DebugUtil.h"
#include "Survivor/Enemy/EnemyBase.h"

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
		AEnemyBase* EnemyActor = Cast<AEnemyBase>(TargetActor);
		if (ensure(EnemyActor))
		{
			PRINT_R("{0}.Hp={1}", EnemyActor->GetActorNameOrLabel(), GetHp());
			EnemyActor->OnHpChanged.Broadcast(GetHp(), GetMaxHp());
		}
	}
	else
	{
		return false;
	}

	return true;
}
