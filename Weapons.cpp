// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons.h"
#include "Components/SkeletalMeshComponent.h"
#include "MainCharacter.h"  // on equip function uses 
#include "Engine/SKeletalMeshSocket.h"  // for socket we added to the character 
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"   // Sound Playing Property
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Enemy.h"

AWeapons::AWeapons()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	CombatCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CombatCollision"));
	CombatCollision->SetupAttachment(GetRootComponent());
	bWeaponParticle = false;

	WeaponState = EWeaponState::EWS_Pickup;

	damage = 25.f;
}

void AWeapons::BeginPlay() 
{
	Super::BeginPlay();
	CombatCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapons::CombatOnOverlapBegin);
	CombatCollision->OnComponentEndOverlap.AddDynamic(this, &AWeapons::CombatOnOverlapEnd);
}

void AWeapons::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (WeaponState==EWeaponState::EWS_Pickup  && OtherActor) //otherActor - which overlaps with area
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);  // if OtherActor can be cast to AMainCharacter then it is Maincharacter

		if (Main)
		{
			// Equip(Main);  // Equip to Main, set sword upon touching it
			Main->SetActiveOverlappingItem(this); // if we are overlapping with item
			 
		}
	}
 }

void AWeapons::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
	if (Main)
	{
		Main->SetActiveOverlappingItem(nullptr); // as soon as we stop overlapping 

	}

 }

void AWeapons::Equip(AMainCharacter* Character)
{
	if (Character) // if character is valid
	{
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore); // Camera doesn't zoom in 
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore); // we don't want collision happening with pawn

		SkeletalMesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* RightHandSocket = Character->GetMesh()->GetSocketByName("RightHandSocket"); 
		if (RightHandSocket)
		{
			RightHandSocket->AttachActor(this, Character->GetMesh());
			bRotate = false;  // as soon as sword attaches to the characte turn off rotation 

			// Character->GetEquippedWeapon()->Destroy();  // Get refrence to EquippedWeapon and Destroy (Previously equipped weapon. When we take the new weapon)
			/* You might get crash if you try to destroy weapon before equipping it  so go to mainchar to implement*/ 
			
			Character->SetEquipedWeapon(this);

			Character->SetActiveOverlappingItem(nullptr);  // In the Game overlapping status changes to null means points to nothing, as soon as we equip we set ActiveOverlapping item to null

		}
		if (OnEquipSound) // Checking if sound selected in blueprint is valid
		{
			UGameplayStatics::PlaySound2D(this, OnEquipSound);
		}
		if (!bWeaponParticle) // idle particle on weapon if we want or not option 
		{
			IdleParticlesComponent->Deactivate(); // deactivate if we don't want idle particle on sword 
		}
	}
}

void AWeapons::CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon Collided"));
	if (OtherActor)
	{
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		if (Enemy)
		{
			if (Enemy->HitParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Enemy->HitParticles,GetActorLocation(), FRotator(0.f), false);
			}
		}
	}

}
void AWeapons::CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{

}



