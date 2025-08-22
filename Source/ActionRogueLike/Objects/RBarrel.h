// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionRogueLike/Interfaces/RGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "RBarrel.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ARBarrel : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ARBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Components
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Cube;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForce;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ExplosionParticle;

	//Functions
	
	UFUNCTION()
	void Explode(AActor* OtherActor);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,
			   AActor* OtherActor,
			   UPrimitiveComponent* OtherComp,
			   FVector NormalImpulse,
			   const FHitResult& Hit);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
