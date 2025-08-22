// Fill out your copyright notice in the Description page of Project Settings.


#include "RChest.h"


// Sets default values
ARChest::ARChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PartDownChest = CreateDefaultSubobject<UStaticMeshComponent>("PartDownChest");
	RootComponent = PartDownChest;

	PartUpChest = CreateDefaultSubobject<UStaticMeshComponent>("PartUpChest");
	PartUpChest->SetupAttachment(PartDownChest);

}

// Called when the game starts or when spawned
void ARChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARChest::Interact_Implementation(APawn* InstigatorPawn)
{
	PartUpChest->SetRelativeRotation(FRotator(110, 0, 0));
}

