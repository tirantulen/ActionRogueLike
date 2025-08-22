// Fill out your copyright notice in the Description page of Project Settings.


#include "RInteractionComponent.h"

#include "ActionRogueLike/Interfaces/RGameplayInterface.h"


// Sets default values for this component's properties
URInteractionComponent::URInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void URInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	TArray<FHitResult> Hits;

	FCollisionShape Shape;
	float Radius = 30.0f;
	Shape.SetSphere(Radius);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);
	for (FHitResult Hit : Hits) {
		AActor* HitActor = Hit.GetActor();
		
		if (HitActor != nullptr)
		{
			
			if (HitActor->Implements<URGameplayInterface>())
			{
			APawn* MyPawn = Cast<APawn>(MyOwner);
			IRGameplayInterface::Execute_Interact(HitActor, MyPawn);
				
			}
		}
	}
	FColor LineColor = bBlockingHit ? FColor::Red : FColor::Green;
	DrawDebugLine(GetWorld(),EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}


