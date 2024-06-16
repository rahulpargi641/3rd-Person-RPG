// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true));
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true));
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true));
	class APawn* Pawn; // reference to Owner pawn (Main Character)  

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true));
	class AMainCharacter* Main;

private:
	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
		void UpdateAnimationProperties(); // similar to BeginPlay()

	virtual void NativeInitializeAnimation() override;
};
