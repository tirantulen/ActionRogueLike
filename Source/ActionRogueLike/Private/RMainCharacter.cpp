// Fill out your copyright notice in the Description page of Project Settings.


#include "RMainCharacter.h"
#include "RMainCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "ActionRogueLike/Components/RInteractionComponent.h"
#include "ActionRogueLike/Interfaces/RAttributesInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARMainCharacter::ARMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Spring arm component set up
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	//Camera component set up
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	//Interaction component
	InteractionComp = CreateDefaultSubobject<URInteractionComponent>("InteractionComp");

	//Attributes component
	AttributesComponent = CreateDefaultSubobject<URAttributesComponent>("AttributesComp");

}

//Interfaces Functions
void ARMainCharacter::ChangeHealthValue_Implementation(float AmountOfDamage)
{
	if (!AttributesComponent->ApplyHealthChange(this,AmountOfDamage)) Destroy();
}

// Called when the game starts or when spawned
void ARMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

// Called every frame
void ARMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//Inputs set up
void ARMainCharacter::SetupPlayerInputComponent(UInputComponent* localInputComponent)
{
	Super::SetupPlayerInputComponent(localInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(localInputComponent))
	{
		Input->BindAction(MoveInput, ETriggerEvent::Triggered, this, &ARMainCharacter::MoveAction);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARMainCharacter::Look);
		Input->BindAction(JumpInput, ETriggerEvent::Started, this, &ARMainCharacter::JumpAction);
		Input->BindAction(JumpInput, ETriggerEvent::Completed, this, &ARMainCharacter::StopJumpingAction);
		Input->BindAction(PrimaryAttackInput, ETriggerEvent::Completed, this, &ARMainCharacter::PrimaryAttack);
		Input->BindAction(PrimaryInteractInput, ETriggerEvent::Completed, this, &ARMainCharacter::PrimaryInteract);
	}
}

void ARMainCharacter::MoveAction(const FInputActionValue& Value)	
{
	FVector2d movementVector = Value.Get<FVector2d>();

	if (Controller != nullptr)
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(forwardDirection, movementVector.Y);
		AddMovementInput(rightDirection, movementVector.X);
	}
}

//Look camera function
void ARMainCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxis = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxis.X);
	AddControllerPitchInput(LookAxis.Y);
}

//Jump function
void ARMainCharacter::JumpAction()
{
	Jump();
}

//Stop jumping function
void ARMainCharacter::StopJumpingAction()
{
	StopJumping();
}

void ARMainCharacter::PrimaryAttack()
{
	PlayAnimMontage(PrimaryAttackAnimation);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ARMainCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ARMainCharacter::PrimaryInteract()
{
	if (InteractionComp != nullptr)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ARMainCharacter::PrimaryAttack_TimeElapsed()
{
	FVector DesirableLocation;
	FVector StartCameraLocation = CameraComp->GetComponentLocation();
	FVector EndCameraLocation = CameraComp->GetComponentLocation() + CameraComp->GetForwardVector() * 6000;
	DesirableLocation = EndCameraLocation;
	FHitResult Hit;
	
	GetWorld()->LineTraceSingleByChannel(Hit, StartCameraLocation, EndCameraLocation, ECollisionChannel::ECC_Visibility);

	if (Hit.bBlockingHit)
	{
		DesirableLocation = Hit.Location;
	}
	FVector SpawnLocation = GetMesh()->GetSocketLocation("WeaponSocket") + GetActorForwardVector()*80;
	FRotator SpawnRotation = (DesirableLocation - StartCameraLocation).Rotation();
	FTransform SpawnTM = FTransform(SpawnRotation,SpawnLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	
	AActor* ActorSpawned = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	
}



