// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ColliderMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UColliderMovementComponent : public UPawnMovementComponent /* -> NavMovementComponent -> UMovementComponent -> UActorComponent inside
																			   TickComponent function

																			   */
																			   
{
	GENERATED_BODY()
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override; // copied from UPawnMovementComponent  inherites from UNavMovementComponent -> UMovementComponent 


	
};
