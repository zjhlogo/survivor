// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Survivor/Util/SurvivorDefine.h"

AItemBase::AItemBase()
{
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetCollisionProfileName(FSurvivorDefine::CollisionProfileItem);
	StaticMeshComp->CanCharacterStepUpOn = ECB_No;
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComp->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnItemPicked);
}

void AItemBase::OnItemPicked(UPrimitiveComponent* OverlappedComponent,
                             AActor* OtherActor,
                             UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex,
                             bool bFromSweep,
                             const FHitResult& SweepResult)
{
	// TODO: fly to player
	// if (UAbilitySystemComponent* Ability = OtherActor->FindComponentByClass<UAbilitySystemComponent>())
	// {
	// 	Ability->ApplyGameplayEffectToSelf(PickedGe.GetDefaultObject(), 0, {});
	// }
}
