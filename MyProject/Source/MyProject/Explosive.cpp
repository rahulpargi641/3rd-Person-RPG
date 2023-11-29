// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosive.h"
#include "MainCharacter.h" // so we know what main character is in the OnOverlapBegin and OnOverlapEnd , when we typecast OtherActor to MainCharacter

AExplosive::AExplosive()
{
	Damage = 50.f;
}

void AExplosive::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor,OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	UE_LOG(LogTemp, Warning, TEXT("Explosive::OnOverlapBegin"));

	if (OtherActor) //  
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);  // if cast fails then Main will be filled null
		if (Main)  // checks if valid and if it's not null then go inside if statement then we can access things in inside of main
		{
			Main->DecrementHealth(Damage);
			Destroy();  // Destroy Bomb

		}
	}
}

void AExplosive::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp,OtherBodyIndex);
	UE_LOG(LogTemp, Warning, TEXT("Explosive::OnOverlapEnd"));
}