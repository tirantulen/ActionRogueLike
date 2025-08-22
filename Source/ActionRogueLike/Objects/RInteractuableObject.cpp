// Fill out your copyright notice in the Description page of Project Settings.


#include "RInteractuableObject.h"

// Sets default values
ARInteractuableObject::ARInteractuableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void ARInteractuableObject::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ARInteractuableObject::OnUse(APawn* PawnInstigator)
{
	
}

// Called every frame
void ARInteractuableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARInteractuableObject::Interact_Implementation(APawn* InstigatorPawn)
{
	OnUse(InstigatorPawn);
}

