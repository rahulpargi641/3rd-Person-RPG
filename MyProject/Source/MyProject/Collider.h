// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Collider.generated.h"

UCLASS()
class MYPROJECT_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = " Mesh")  // Garbage collected Uproperty
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Sphere")
		class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Sphere")
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Sphere")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UColliderMovementComponent* OurMovementComponent;    // Our own custom movement component

private:
	FVector2D CameraInput;


public:	
	// Sets default values for this pawn's properties
	ACollider();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;  // Going to overide GetMovement Function

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() { return MeshComponent;}   // Getter
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* mesh) { MeshComponent = mesh; }  // Setter
	FORCEINLINE USphereComponent* GetShpereComponent(){ return SphereComponent; }
	FORCEINLINE void SetSphereComponent(USphereComponent* sphere){ SphereComponent = sphere; }

	FORCEINLINE UCameraComponent* GetCameraComponent() { return Camera; }   
	FORCEINLINE void SetCameraComponent(UCameraComponent* camera) { Camera = camera; }                 
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() { return SpringArm; }
	FORCEINLINE void SetSpringArmComponent(USpringArmComponent* springArm) { SpringArm = springArm; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	void MoveForward(float input);
	void MoveRight(float input);

	void CameraPitch(float inputAxis);
	void CameraYaw(float inputAxis);
};
