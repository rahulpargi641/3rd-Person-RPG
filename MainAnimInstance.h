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

		virtual void NativeInitializeAnimation() override;
	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties(); // similar to BeginPlay()

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true));
	float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true));
	bool bIsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true));
	class APawn* Pawn; // refrence to character Owner pawn  

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true));
	class AMainCharacter* Main;
};
