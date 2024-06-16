// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDOverlayAsset) // if in blueprint we selected HUDOvelayAsset
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);   
	}

	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);  // E for enmus, HUD visiblity   
}