// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UENUM(BlueprintType) // Unreal Engine enums
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),// Display names =  for reflection system and blueprints
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),

	EMS_MAX UMETA(DisplayName = "Default MAX")


};          // class - Making enums scoped, it will prevent enums accessed without fully qulify names enums class

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal UMETA(DislplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering UMETA(DislplayName = "ExhaustedRecovering"),

	ESS_MAX UMETA(DisplayName = "Default MAX")

};

UCLASS()
class MYPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	TArray<FVector> PickupLocations; // for debugging purposes
	UFUNCTION(BlueprintCallable)
	void ShowPickupLocations();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
		EMovementStatus MovementStatus;   // What movement status character is in given time

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;	

	// setter function for StaminaStatus
	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	// Set Movement Status and Movement Speed
	void SetMovementStatus(EMovementStatus MovementStatus);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float SprintingSpeed;

	// shift key down or not 
	bool bShitKeyDown;

	/** Pressed Down to enable sprinting*/
	void ShiftKeyDown();
	
	/**Released to stop sprinting*/
	void ShiftKeyUp();
	 
	// Positioning the Camera behind the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true));
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true));
	class UCameraComponent* FollowCamera;

	/** Base turn rate to scale turning functions for the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;  // keyboard movement

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)	
	float BaseLookUpRate;    // keyboard movement

	bool bLMBDown;
	void LMBDown();
	void LMBUp();

	/*
	/*
	/* Player Stats
	/*
	/*
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Coins;  // Cross platform strenghen version of int , 32 bits  

	void DecrementHealth(float Amount);
	void Die();
	void IncrementCoins(int32 Amount);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** called for forward/backwards input*/
	void MoveForward(float value);
	
	/** callded for side to side input*/
		void MoveRight(float value);

		/** called via input to turn at a given rate
		* @parm rate This is a normalized rate, i.e. 1.0 means 100% of desired look up/down rate
		*/
		void TurnRate(float rate);

		/** called via input to look up/down at a given rate
		* @parm rate This is a normalized rate, i.e. 1.0 means 100% of desired look up/down rate
		*/
		void LookUpRate(float rate);

		FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
		FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
			class AWeapons* EquippedWeapon;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
		class AItem* ActiveOverlappingItem; 

		//FORCEINLINE void SetEquipedWeapon(AWeapons* WeaponToSet) { EquippedWeapon = WeaponToSet; }
		void SetEquipedWeapon(AWeapons* WeaponToSet);
		FORCEINLINE AWeapons* GetEquippedWeapon(){ return EquippedWeapon; }

		FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anims")
		bool bAttacking;

		void Attack();

		UFUNCTION(BlueprintCallable)
			void AttackEnd();  // will be called from animation blueprint

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
		class UAnimMontage* CombatMontage;

};
