// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionRogueLike/Interfaces/RGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "RInteractuableObject.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARInteractuableObject : public AActor, public IRGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);
	
public:	
	// Sets default values for this actor's properties
	ARInteractuableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Components
	UPROPERTY(VisibleAnywhere)
	UMeshComponent* Mesh;

	//Functions
	UFUNCTION()
	virtual void OnUse(APawn* PawnInstigator);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
