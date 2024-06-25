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
	StaticMeshComp->SetCollisionProfileName(FSurvivorDefine::CollisionProfileCharacterProjectile);
	StaticMeshComp->CanCharacterStepUpOn = ECB_No;
	StaticMeshComp->SetGenerateOverlapEvents(false);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

void AProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// ignore caster collision
	StaticMeshComp->IgnoreActorWhenMoving(GetInstigator(), true);
	OnActorHit.AddDynamic(this, &AProjectileBase::OnHit);
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBase::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (auto TargetAsc = OtherActor->FindComponentByClass<UAbilitySystemComponent>())
	{
		auto Pawn = GetInstigator();
		if (!ensure(Pawn))
		{
			return;
		}

		auto SourceAsc = Pawn->FindComponentByClass<UAbilitySystemComponent>();
		if (!ensure(SourceAsc))
		{
			return;
		}

		SourceAsc->ApplyGameplayEffectToTarget(HitGe.GetDefaultObject(), TargetAsc);
	}
}
