// Fill out your copyright notice in the Description page of Project Settings.


#include "Collider.h"
#include "Components\StaticMeshComponent.h"
#include "Components\SphereComponent.h"
#include "UObject\ConstructorHelpers.h"
#include "Components\InputComponent.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "ColliderMovementComponent.h"



// Sets default values
ACollider::ACollider()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("root component"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SPhere component"));
	SetRootComponent(SphereComponent);
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn")); // means it can collide with pawn 90%  

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MEsh component"));  // Ustatic mesh is object type and have property variable UStaticmesh
	MeshComponent->SetupAttachment(GetRootComponent());

	// How to set staticMesh from code
	static ConstructorHelpers::FObjectFinder <UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")); // Searching for staticmesh in this path
	if (MeshComponentAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshComponentAsset.Object);    // MeshcomponentAsset has a member variable object, That is where staticmesh from this path is stored
		MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
		MeshComponent->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f)); 
	}


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.f;   // keeps the camera particular distance away
	SpringArm->bEnableCameraLag = true; // Smooth trailing behind our pawn according to camera lag speed
	SpringArm->CameraLagSpeed = 3.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAmera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	OurMovementComponent = CreateDefaultSubobject<UColliderMovementComponent>(TEXT("OUrMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;

	CameraInput = FVector2D(0.f, 0.f);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}                


// Called when the game starts or when spawned
void ACollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = GetActorRotation();  // To look up-down and side to side  
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);      // Remember Actually this Rotates pawn
	
	FRotator NewSpringArmRotation = SpringArm->GetComponentRotation();
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch += CameraInput.Y, -80.f, -15.f);  // Restrict y player movement
	SpringArm->SetWorldRotation(NewSpringArmRotation);

}

// Called to bind functionality to input
void ACollider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACollider::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACollider::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &ACollider::CameraPitch);
	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &ACollider::CameraYaw);

}

void ACollider::MoveForward(float input)  // functions in unreal editor input settings
{
	FVector Forward = GetActorForwardVector();
	if (OurMovementComponent)    // Instead of checking movement component we are checking OurMovement component
	{
		OurMovementComponent->AddInputVector(Forward * input); 
	}
}


void ACollider::MoveRight(float input)  // functions in unreal editor input settings
{
	FVector Right = GetActorRightVector();
	if (OurMovementComponent)
	{
		OurMovementComponent->AddInputVector(Right * input);
	}
}

void ACollider::CameraPitch(float axisValue)
{
	CameraInput.Y = axisValue; 
}

void ACollider::CameraYaw(float axisValue)
{
	CameraInput.X = axisValue;
}

UPawnMovementComponent* ACollider::GetMovementComponent() const
{
	return OurMovementComponent;   // Our custom MovementCOmponent derives from UPawnMovementComponent* so we can indeed return OurMovementComponent in form UPawnMovement Component, 
	                                //parent of our custom Movement Component
}


