// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class MYPROJECT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "ActorMeshComponenets")
	   UStaticMeshComponent* StaticMesh;

	// Location used by SetActorLocation when BeginPlay() is called
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Floater Variables")
	   FVector InitialLocation;

	// Location of the Actor when dargged in from the editor
	UPROPERTY(VisibleInstanceOnly,BlueprintReadWrite, Category = "Floater Variables")
	    FVector PlacedLocation;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Floater Variables")
		bool bInitializeFloaterLocations;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Floater Variables")
        FVector WorldOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floater Variables")
		FVector InitialDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floater Variables")
		bool bShouldFloat;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")
		FVector InitialForce;

private:
	float RunningTime;
	float BaseZLocation;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floater Variables");
	float A;  // Amplitue - How much we oscillate up and down
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floater Variables");
	float B; // Period -> 2 *PI / ABS(B)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floater Variables");
	float C; // Phase shift  start at the lower position Shifts the wave  C / B  , Time axis(X) shift, results in start and end at different point, Lower than Defualt Amplitude
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floater Variables");
	float D; // Vertical shift - Start Oscillation at +500 units higher or -500 lower, shifts entire wave



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
