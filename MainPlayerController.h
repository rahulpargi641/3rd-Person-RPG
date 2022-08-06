// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

		/** Refrence to the UMG asset in the editor */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> HUDOverlayAsset;  // It will give opportunity to choose this in PlayerController Blueprint

	/** Variable to hold widget after creating it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* HUDOverlay;

protected:
	virtual void BeginPlay() override;
	
};
