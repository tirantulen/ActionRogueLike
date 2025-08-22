// Fill out your copyright notice in the Description page of Project Settings.


#include "RMagicProjectile.h"

#include "ActionRogueLike/Interfaces/RAttributesInterface.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ARMagicProjectile::ARMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SpereComp");
	RootComponent = SphereComp;
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ARMagicProjectile::OnHit);

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	ParticleComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 3000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->MaxSpeed = 4000.0f;
	MovementComp->ProjectileGravityScale = 0.0f;

	AudioComp = CreateDefaultSubobject<UAudioComponent>("SoundComp");
	AudioComp->SetupAttachment(SphereComp);
	
}

// Called when the game starts or when spawned
void ARMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARMagicProjectile::Explode(AActor* OtherActor)
{
	FTransform Transform = FTransform(GetActorRotation(), GetActorLocation(), FVector(2, 2, 2));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, Transform);
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSoundCue, GetActorLocation());
	if (GetInstigator() != OtherActor)
	{
		if (OtherActor->Implements<URAttributesInterface>()) IRAttributesInterface::Execute_ChangeHealthValue(OtherActor, -30.0f);
	}
	Destroy();
}

void ARMagicProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Explode(OtherActor);
}



