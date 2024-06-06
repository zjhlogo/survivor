// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Survivor/Util/SurvivorDefine.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	InitialLifeSpan = 5.0f;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetCollisionProfileName(FSurvivorDefine::CollisionProfilePawnProjectile);
	StaticMeshComp->CanCharacterStepUpOn = ECB_No;
	StaticMeshComp->SetGenerateOverlapEvents(false);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	// ignore caster collision
	StaticMeshComp->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	StaticMeshComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (UAbilitySystemComponent* Ability = OtherActor->FindComponentByClass<UAbilitySystemComponent>())
	{
		Ability->ApplyGameplayEffectToSelf(HitGe.GetDefaultObject(), 0, {});
	}
}
