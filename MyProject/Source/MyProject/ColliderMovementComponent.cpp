// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovementComponent.h"


void UColliderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); // Call to parent version, whatever is in the paremt gets called

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))  // MovementComponent has variable PawnOwner, OwningPawn that owns this movement component(who owns this movement component)
		                                                                 // we are going to own MovementComponent from Collider we are checking to see if its valid if its not valid then there's no reason to comtinue. UpdatedComponent->
	{   //The component we move and update. If this is null at startup and bAutoRegisterUpdatedComponent is true, the owning Actor's root component will automatically 
		//be set as our UpdatedComponent at startup.
		return;
	}

	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f);  // MovementComponent has InputVector info and ConsumeInputVector() reset to zero
	                                                                      

	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;  // FHitResult is a structure, stores Hit inforamtion
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit); // (Direction and magnitude, Rotation, )  FhitResult stores information regarading hit
		                                                                                             // true , checks if we hit something, and if we did store the info in the FResult
		// If we hit or bump into something, slide along the side of it
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1 - Hit.Time, Hit.Normal, Hit);
			UE_LOG(LogTemp, Warning, TEXT("Valid Blocking Hit"));
		}
	}
}