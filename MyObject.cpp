// Fill out your copyright notice in the Description page of Project Settings.


#include "MyObject.h"

UMyObject::UMyObject() 
{
	var = 0.f;
}

void UMyObject::VFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("This is our warning text"));
}


