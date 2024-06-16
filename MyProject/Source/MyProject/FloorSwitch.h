// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class MYPROJECT_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();

	/**Overlap volume for functionality to be triggered
	*/
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category ="Flooe Switch")
	class UBoxComponent* TriggerBox;

	/*Switch for the character to step on
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Flooe Switch")
		class UStaticMeshComponent* FloorSwitch;
	/*Door to move when the floor switch in stepped on
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Flooe Switch")
		class UStaticMeshComponent* Door;
	
	/** Initial Locaton for Door*/
	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
		FVector InitialDoorLocation;

	/*Initial Location For DoorSwitch*/
	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
		FVector InitialDoorSwitchLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Switch")
		float SwitchTime;

	FTimerHandle SwitchHandle;
	bool bCharacterOnSwitch;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	             // Parameter inside - Functions bound to delegate
	UFUNCTION()
	    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category ="Floor Switch") // don't have to give functionlity in c++, in blueprint
		void RaiseDoor(); // In Blueprint red nodes are for events 

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
		void LowerDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch") // don't have to give functionlity in c++, in blueprint
		void RaiseFloorSwitch(); // In Blueprint red nodes are for events

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
		void LowerFloorSwitch();   // GetDeltaSeconds in Blueprint- How much time has passed since previous frame

	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
		void UpdateDoorLocation(float Z);

	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
		void UpdateFloorSwitchLocation(float Z);

	void CloseDoor();
};


