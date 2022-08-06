// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class MYPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	/** Base Shape Collision*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="Item|Collision")
		class USphereComponent* CollisionVolume;
	/**Base Mesh Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Mesh")
	class UStaticMeshComponent* Mesh;   // UStaticMesh need not to be constructed, selected in the blueprint, UStaticMeshComponent needs to be constructed

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Particles")
	class UParticleSystemComponent* IdleParticlesComponent;  // UParticleSystem need not to be constructed, selected in the blueprint

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Particles")
		class UParticleSystem* OverlapParticles;  // It keep being null until it sets in blueprint

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Sound")
		class USoundCue* OverlapSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|ItemProperties")
		bool bRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Sound")
		float RotationRate;   

	// Player Controller -  Posses pawn, you posses and unposses other pawn, Information on HUD still stay

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
