// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapons.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Pickup		UMETA(DisplayName = "Pickup"),
	EWS_Equipped	UMETA(DisplayName = "Equipped"),

	EWS_Max			UMETA(DislplayName= "DefaultMax")
};

UCLASS()
class MYPROJECT_API AWeapons : public AItem
{
	GENERATED_BODY()
public:
	AWeapons();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		EWeaponState WeaponState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles")
		bool bWeaponParticle; // if we want weapon particles after equiping

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Skeletal Mesh")
		class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item | Combat")
		class UBoxComponent* CombatCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Combat")
	float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
		class USoundCue* OnEquipSound;

	protected:
		virtual void BeginPlay() override;


	public:
	// UFUNCTION()  - Inherited Function cannot be marked UFUNCTION, it will inherit From the parent class 
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void Equip(class AMainCharacter* Character);

	FORCEINLINE void SetWeaponState(EWeaponState State) { WeaponState = State; }
	FORCEINLINE EWeaponState GetWeaponState() { return WeaponState; }

	void CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
