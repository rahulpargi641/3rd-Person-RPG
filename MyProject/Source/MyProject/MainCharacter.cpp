// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "Math/RotationMatrix.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapons.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"  // for AnimInstance


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Camera Boom (pulls towrads the player if there's a collision
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CAmeraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 500.f;  // Camera follows at this distance
	CameraBoom->bUsePawnControlRotation = true;  // Rotate arm based on controller class on the pawn .. controller is the class of pawn

	// Set size of collision capsule
	GetCapsuleComponent()->SetCapsuleSize(44,109);  // We can hard code value cuz we are not gonna change.

	// Create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAmera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);           // Attaching camera to the CameraBoom and functionality to attach meshes to socket
	FollowCamera->bUsePawnControlRotation = false;  // Attach the camera to the end of the boom and let the boom adjust to the match the controller orientation
	// we want camera to follow CameraBoom's rotation   
	
	// Set out turn rates for inputs
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	// Don't rotate when controller rotates, Let that just affect the camera
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Configure Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character Moves in direction of keyboard input. 
	//If true, rotate the Character toward the direction of acceleration, using RotationRate as the rate of rotation change.
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;


	MaxHealth = 100.f;
	Health = 60.f;
	MaxStamina = 400.f;
	Stamina = 200.f;
	Coins = 0;

	RunningSpeed = 700;
	SprintingSpeed = 1500;

	bShitKeyDown = false;
	bLMBDown = false;

	StaminaDrainRate = 10;
	MinSprintStamina = 100;

	// Initialize enums
	MovementStatus = EMovementStatus::EMS_Normal;
	StaminaStatus = EStaminaStatus::ESS_Normal;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	UKismetSystemLibrary::DrawDebugSphere(this, GetActorLocation() + FVector(0, 0, 75.f), 25.f, 8,FLinearColor::Green, 10.f, .5f ); // sphere above character's head, 12 is a segement value

	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DeltaStamina = StaminaDrainRate * DeltaTime;// DeltaStamina - How much the stamina should change in particular frame in order to drain or recover 
	switch (StaminaStatus)
	{
	case EStaminaStatus::ESS_Normal:
		if (bShitKeyDown)
		{
			if (Stamina - DeltaStamina <= MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_BelowMinimum);
				Stamina -= DeltaStamina;
			}
			else
			{
				Stamina -= DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Sprinting);
		}
		else  // Shift key up
		{
			if (Stamina+DeltaStamina >= MaxStamina) 
			{
				Stamina = MaxStamina;
			}
			else
			{
				Stamina += DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
			break;  // if you don't break it will go through the next state 

	case EStaminaStatus::ESS_BelowMinimum:
		if (bShitKeyDown)
		{
			if (Stamina <= 0.f)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
				Stamina = 0.f;
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			else
			{
				Stamina -= DeltaStamina;
				SetMovementStatus(EMovementStatus::EMS_Sprinting);
			}
		}
		else // Shift key is up
		{
			if (Stamina += DeltaStamina > MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
				Stamina += DeltaStamina;
			}
			else
			{
				Stamina += DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		    
		}
				break;

	case EStaminaStatus::ESS_Exhausted:
		if (bShitKeyDown)
		{
			Stamina = 0.f;
		}
		else // Shift key is up
		{
			SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
			Stamina += DeltaStamina;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);

		break;

	case EStaminaStatus::ESS_ExhaustedRecovering:
		if (Stamina + DeltaStamina > MinSprintStamina)
		{
			SetStaminaStatus(EStaminaStatus::ESS_Normal);
			Stamina += DeltaStamina;
		}
		else
		{
			Stamina += DeltaTime;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);
        break;

	default:
		; // if you don't have anything to do with default , just empty statement 
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);  // checks for player input component, halts the execution if PlayerInputComponent false

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);  // Jump - Function from the character class
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::ShiftKeyDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::ShiftKeyUp);

	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMainCharacter::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this, &AMainCharacter::LMBUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	// whenever mouse is moving that value is going to be returned and fed into the function we give it
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);  // Function from the Pawn class(AddControllerYawInput)
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpRate);

}

/** Called for forward/backwards input*/
void AMainCharacter::MoveForward(float value) 
{
	if ((Controller != nullptr) && (value != 0.0f) && (!bAttacking))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction= FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);  // Gives Forward Vector
		AddMovementInput(Direction, value);
	
	}

}

void AMainCharacter::MoveRight(float value)
{
	if ((Controller != nullptr) && (value != 0.0f)&& (!bAttacking))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);  // gives Right vector
		AddMovementInput(Direction, value);

	}
}

void AMainCharacter::TurnRate(float rate)
{
	/** UWorld made available to you through a Getter method(GetWorld) 
	* GetWorld() will return a pointer type
	* UWorld is our blueprint, and we could construct it using a method called the constructor.
	*/
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());    // Get Deltatime outside of tick function
}

void AMainCharacter::LookUpRate(float rate)
{
	AddControllerYawInput(rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());  // 
}

void AMainCharacter::LMBDown()
{
	bLMBDown = true;
	if (ActiveOverlappingItem)  // Checking to see if character overlapping with item
	{
		// Casting Item to weapon
		AWeapons* Weapon = Cast<AWeapons>(ActiveOverlappingItem);
		if (Weapon) // if casting is successful
		{
			Weapon->Equip(this);
			SetActiveOverlappingItem(nullptr);  // After equipping the item/sword setting the overlap false 

		}
	}
	else if (EquippedWeapon)  // Item is equipped
	{
		Attack();
	}



}
void AMainCharacter::LMBUp()
{
	bLMBDown = false;
}


void AMainCharacter::DecrementHealth(float Amount)
{
	if (Health <= 0.f)
	{
		Health -= Amount;  // Empty the health in the Health bar and then we die
		Die();
	}
	else
	{
		Health -= Amount;
	}
}

void AMainCharacter::Die()
{
	
}

void AMainCharacter::IncrementCoins(int32 Amount)
{
	Coins += Amount;
}


void AMainCharacter::SetMovementStatus(EMovementStatus Status)
{
	MovementStatus = Status;
	if (MovementStatus == EMovementStatus::EMS_Sprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;  
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void AMainCharacter::ShiftKeyDown()
{
	bShitKeyDown = true;
	UE_LOG(LogTemp, Warning, TEXT("Shift Key Down"));
}

void AMainCharacter::ShiftKeyUp()
{
	bShitKeyDown = false;
	UE_LOG(LogTemp, Warning, TEXT("Shift Key Up"));

}

void AMainCharacter::ShowPickupLocations()
{
	/* for (int32 i = 0; i < PickupLocations.Num(); i++)
	{
		UKismetSystemLibrary::DrawDebugSphere(this,PickupLocations[i], 25.f, 8, FLinearColor::Green, 10.f, 0.5f);
	}  */

	for (auto Location : PickupLocations)
	{
		UKismetSystemLibrary::DrawDebugSphere(this, Location, 25.f, 8, FLinearColor::Green, 10.f, 0.5f);
	}
}

void AMainCharacter::SetEquipedWeapon(AWeapons* WeaponToSet)
{
	if (EquippedWeapon) // If EquippedWeaonn is valid , then only destroy EquippedWeapon
	{
		EquippedWeapon->Destroy(); // if you try to call to function which is null, that will cause a crash
		// Crash in UE - Array elements out of bound, derefrencing the pointers

		// Just because you called Destroy on something it's not deleted just yet until the Garbage collector system gets around to it
	}
	EquippedWeapon = WeaponToSet;  


}

void AMainCharacter::Attack()
{
	if (!bAttacking)  // Only Want to Attack if bLMBDown is false, Means if we are not attacking then we attack, this takes care of 
	{                 // You can not attack until Attack Animation completes
		bAttacking = true;

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && CombatMontage) 
		{
			int32 Section = FMath::RandRange(0, 1);
			switch (Section)
			{
			case 0:
				AnimInstance->Montage_Play(CombatMontage, 2.2f); // 1.35 will at speed 35 percent faster 
				AnimInstance->Montage_JumpToSection(FName("Attack_1"), CombatMontage); 
				break;
			case 1:
				AnimInstance->Montage_Play(CombatMontage, 1.8);
				AnimInstance->Montage_JumpToSection(FName("Attack_2"), CombatMontage);
				break;
			default:
				;
			}
			
		}
	}
}

void AMainCharacter::AttackEnd()
{
	bAttacking = false; // After the Attack Animation is completed you can run again means you get to Regular Walk/Run Animation

	if (bLMBDown)  // if mouse button is down, Hold Mouse Button Down keep Attacking
	{
		Attack();
	}
}