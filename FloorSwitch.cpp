 // Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
AFloorSwitch::AFloorSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("trigger box"));
	RootComponent = TriggerBox; // If the root component moves it will move the door not vice versa

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // Physics- collide, QueryOnly- not collide, only overlap and overlap events
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore); // not fire off any events when collides or overlap with anything
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);// ECR- ECollisionResponse, convention in UE
	                                                                                                        // Use this convention when creating your own enums
	TriggerBox->SetBoxExtent(FVector(62.f, 62.f, 32.f));
	
	FloorSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor Swithch"));
	FloorSwitch->SetupAttachment(GetRootComponent());
	
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(GetRootComponent());

	SwitchTime = 2.f;
	bCharacterOnSwitch = false;
}

// Called when the game starts or when spawned
void AFloorSwitch::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapBegin); // Actors inherits FComponentBeginOverlapSinature* OncomponentBeginOverlap
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapEnd); // Actors inherits FComponentBeginOverlapSinature* OncomponentBeginOverlap
																						 // from the PrimitiveComponent.h class. AddDynamics is a macro
	InitialDoorLocation = Door->GetComponentLocation();
	InitialDoorSwitchLocation = FloorSwitch->GetComponentLocation();

	
}

// Called every frame
void AFloorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin."));
	if (!bCharacterOnSwitch) bCharacterOnSwitch = true;
	RaiseDoor();
	LowerFloorSwitch();
}

void AFloorSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End."));
	if (bCharacterOnSwitch) bCharacterOnSwitch = false;

	GetWorldTimerManager().SetTimer(SwitchHandle, this, &AFloorSwitch::CloseDoor, SwitchTime);  // Gets WorldTimerManager and it WorldTimerManager sets Timer
}

void AFloorSwitch::UpdateDoorLocation(float Z)
{
	FVector NewLocation = InitialDoorLocation;
	NewLocation.Z += Z;
	Door->SetWorldLocation(NewLocation);  // Sets location in world
}

void AFloorSwitch::UpdateFloorSwitchLocation(float Z)
{
	FVector NewLocation = InitialDoorSwitchLocation;
	NewLocation.Z += Z;
	FloorSwitch->SetWorldLocation(NewLocation);
}

void AFloorSwitch::CloseDoor()
{
	if (!bCharacterOnSwitch) // At the end of the timer if character is not on the switch then only lower door and raise switch
	{
		LowerDoor();
		RaiseFloorSwitch();
	}
	
}
