// Fill out your copyright notice in the Description page of Project Settings.


#include "RBarrel.h"

#include "ActionRogueLike/Interfaces/RAttributesInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
ARBarrel::ARBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>("Cube");
	Cube->SetCollisionProfileName("PhysicsActor");
	RootComponent = Cube;
	Cube->OnComponentHit.AddDynamic(this, &ARBarrel::OnHit);

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->Radius = 1000.0f;
	RadialForce->bImpulseVelChange = true;

	

}

// Called when the game starts or when spawned
void ARBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARBarrel::Explode(AActor* OtherActor)
{
	FTransform Transform = FTransform(GetActorRotation(), GetActorLocation(), FVector(2, 2, 2));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, Transform);
	RadialForce->FireImpulse();
	if (OtherActor->Implements<URAttributesInterface>()) IRAttributesInterface::Execute_ChangeHealthValue(OtherActor, -30.0f);
	Destroy();
	
}

void ARBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Explode(OtherActor);
}



