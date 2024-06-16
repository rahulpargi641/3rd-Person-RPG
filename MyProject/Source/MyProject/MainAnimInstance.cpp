// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
//#include "GameFramework/PawnMovementComponent.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacter.h" // we need for casting


void UMainAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner(); 
		if (Pawn)
		{
			Main = Cast<AMainCharacter>(Pawn);
		}
	}
}

void UMainAnimInstance::UpdateAnimationProperties() 
{
	if (Pawn == nullptr) // Upper code will already set the pawn but just be sure
	{
		Pawn = TryGetPawnOwner();  // Get pawn owner of animationInstance
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity(); // we want velocity only in horizontal direction 
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f); // don't want to change animation other than horizontal and vertical direction
		MovementSpeed = LateralSpeed.Size();  // scaler value of vector

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();  

		if (Main == nullptr)
		{
			Main = Cast<AMainCharacter>(Pawn); // Now we should be able to have access to main straigth from blueprint without having to GetPawnOwner node
		}
	}
}