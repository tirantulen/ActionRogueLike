// Fill out your copyright notice in the Description page of Project Settings.


#include "RBlackHole.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "PhysicsEngine/ShapeElem.h"

// Sets default values
ARBlackHole::ARBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ARBlackHole::OnHit);
	SphereComp->SetNotifyRigidBodyCollision(true);
	RootComponent = SphereComp;

	BlackHoleParticle = CreateDefaultSubobject<UParticleSystemComponent>("BlackHoleParticle");
	BlackHoleParticle->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 500.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->MaxSpeed = 500.0f;
	MovementComp->ProjectileGravityScale = 0.0f;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(SphereComp);
	RadialForceComp->ImpulseStrength = -210;
	RadialForceComp->Radius = 5000;
	RadialForceComp->AddCollisionChannelToAffect(ECC_PhysicsBody);
	RadialForceComp->bImpulseVelChange = true;

}


// Called when the game starts or when spawned
void ARBlackHole::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ARBlackHole::Attract, 0.1f, true);

	GetWorldTimerManager().SetTimer(TimerHandleDestroyActor, this, &ARBlackHole::DestroyBlackhole, 5.0f, false);
	
}

void ARBlackHole::Attract()
{
	RadialForceComp->FireImpulse();
}

void ARBlackHole::DestroyBlackhole()
{
	Destroy();
}



void ARBlackHole::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherComp && OtherComp->IsSimulatingPhysics())
	{
		UE_LOG(LogTemp, Warning, TEXT("Destruyendo %s"), *OtherActor->GetName());
		OtherActor->Destroy();
	}
}



// Called every frame
void ARBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

