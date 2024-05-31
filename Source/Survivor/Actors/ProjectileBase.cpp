// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Survivor/Enemy/EnemyBase.h"
#include "Survivor/Util/SurvivorDefine.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	InitialLifeSpan = 5.0f;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetCollisionProfileName(USurvivorDefine::CollisionProfileProjectile);
	StaticMeshComp->CanCharacterStepUpOn = ECB_No;

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
	StaticMeshComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void AProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorHit.AddDynamic(this, &AProjectileBase::OnHit);
}

void AProjectileBase::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor))
	{
		UAbilitySystemComponent* Ability = Enemy->GetAbilitySystem();
		Ability->ApplyGameplayEffectToSelf(OnHitEffect.GetDefaultObject(), 0, {});
	}
}
