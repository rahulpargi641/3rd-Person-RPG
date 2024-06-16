// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Critter.generated.h"     // Always keep this header file last

UCLASS()
class MYPROJECT_API ACritter : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Mesh")
		//class UStaticMeshComponent* MeshComponent;
		class USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Pawn Movement")
		float MaxSpeed;

public:
	// Sets default values for this pawn's properties
	ACritter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float value);
	void MoveRight(float value);

	FVector CurrentVelocity;
};
