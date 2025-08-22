#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ActionRogueLike/Components/RAttributesComponent.h"
#include "ActionRogueLike/Interfaces/RAttributesInterface.h"
#include "RMainCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class URInteractionComponent;
class URAnimationComponent;

UCLASS()
class ACTIONROGUELIKE_API ARMainCharacter : public ACharacter, public IRAttributesInterface
{
	GENERATED_BODY()

	virtual void ChangeHealthValue_Implementation(float AmountOfDamage) override;


public:
	// Sets default values for this character's properties
	ARMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Components:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	URInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URAttributesComponent* AttributesComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	UAnimMontage* PrimaryAttackAnimation;

	UPROPERTY(VisibleAnywhere)
	FTimerHandle TimerHandle_PrimaryAttack;
	
	//Inputs:

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveAction(const FInputActionValue& value);
	void Look(const FInputActionValue& Value);
	void JumpAction();
	void StopJumpingAction();
	void PrimaryAttack();
	void PrimaryInteract();
	void PrimaryAttack_TimeElapsed();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveInput;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpInput;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* PrimaryAttackInput;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* PrimaryInteractInput;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
