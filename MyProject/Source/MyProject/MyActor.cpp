// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components\StaticMeshComponent.h"

// Sets default values
AMyActor::AMyActor()     // Constructor
{
    //Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));
	InitialLocation = FVector(0.0f);
	PlacedLocation = FVector(0.0f);
	WorldOrigin = FVector(0.0f);

	InitialDirection = FVector(0.0f, 0.0f, 0.0f);       

	bInitializeFloaterLocations = false;
	bShouldFloat = false;

	InitialForce = FVector(50000.f, 0.f, 0.f);

	RunningTime = 0.f;

	A = 0.f;
	B = 0.f;
	C = 0.f;
	D = 0.f;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	float InitialX = FMath::FRand();
	float InitialY = FMath::FRandRange(-100.f, 100.f);
	float InitialZ = FMath::FRandRange(50.f,50.f);

	InitialLocation.X = InitialX;
	InitialLocation.Y = InitialY;
	InitialLocation.Z = InitialZ;

	InitialLocation *= 20.f;
	
	// For Sinosudal Movement
	PlacedLocation = GetActorLocation();
	BaseZLocation = PlacedLocation.Z;  // Base or Starting Location of the Actor, to check how small is sine function

	if (bInitializeFloaterLocations) 
	{
		SetActorLocation(InitialLocation);
	}

	//AddActorLocalRotation(Rotation);
	//AddActorWorldOffset(LocalOffset, true, &HitResult); // Vectors are Additive 
	//AddActorLocalOffset(LocalOffset, true, &HitResult); // Constructor

	//StaticMesh->AddForce(InitialForce);
	//StaticMesh->AddTorqueInRadians(InitialForce);  
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldFloat) // Enable or Disable Oscillatory Motion float in the air
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Z =   A * FMath::Sin(B * RunningTime - C) + D;  // Period - 2 * PI / ABS(B),   Modified sine function
		              // A -> Absolute value of A is Amplitude, because value of sine function is small we need to multiply by amplitude
		SetActorLocation(NewLocation);

		RunningTime += DeltaTime;

	    //FHitResult HitResult;
		//AddActorLocalOffset(InitialDirection, true, &HitResult);

		//FVector HitLocation = HitResult.Location;
		//UE_LOG(LogTemp, Warning, TEXT(" Hit Location: X=%f, Y=%f, Z=%f "), HitLocation.X, HitLocation.Y, HitLocation.Z);
		UE_LOG(LogTemp, Warning, TEXT(" Hit Location: X=%f, Y=%f, Z=%f "));

		FRotator Rotation = FRotator(1.f, 0.f, 0.f);
	    AddActorLocalRotation(Rotation);
	}

}

