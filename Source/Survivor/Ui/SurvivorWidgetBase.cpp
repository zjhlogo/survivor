// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorWidgetBase.h"

void USurvivorWidgetBase::SetActorOwner(AActor* Owner)
{
	ActorOwner = Owner;
	OnActorOwnerSet();
}

void USurvivorWidgetBase::OnActorOwnerSet()
{
}
