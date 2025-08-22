// Fill out your copyright notice in the Description page of Project Settings.


#include "RTeleportProjectile.h"

#include "Projects.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ARTeleportProjectile::ARTeleportProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SpereComp");
	RootComponent = SphereComp;
	SphereComp->SetSphereRadius(50.0f);
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ARTeleportProjectile::OnHit);
	
	ProjectileParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileParticle"));
	ProjectileParticle->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	MovementComp->InitialSpeed = 3000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->MaxSpeed = 4000.0f;
	MovementComp->ProjectileGravityScale = 0.0f;
	
}



// Called when the game starts or when spawned
void ARTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandleDestroyActor, this, &ARTeleportProjectile::DestroyActor, 1.0f);
}

void ARTeleportProjectile::Explode(AActor* OtherActor)
{
	FTransform Transform = FTransform(GetActorRotation(), GetActorLocation(), FVector(2, 2, 2));
	GetInstigator()->TeleportTo(Transform.GetLocation() + (0,0,100),GetInstigator()->GetActorRotation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, Transform);
	Destroy();
}

void ARTeleportProjectile::DestroyActor()
{
	Explode(GetInstigator());
}

void ARTeleportProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 FVector NormalImpulse, const FHitResult& Hit)
{
	Explode(OtherActor);
	 
}

// Called every frame
void ARTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

