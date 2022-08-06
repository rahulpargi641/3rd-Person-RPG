// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable) 
class MYPROJECT_API UMyObject : public UObject
{

	GENERATED_BODY()

public:
		UMyObject();

	UPROPERTY(BlueprintReadWrite, category = "Vvariables")
	float var;
	
	UFUNCTION(BlueprintCallable, category = "Vfunctions")
	void VFunction();

    

	
};
