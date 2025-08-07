// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "DynamicFloatCurve.generated.h"

/**
 * 
 */
UCLASS()
class LOCSIM_DT_API UDynamicFloatCurve : public UCurveFloat
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="DynamicCurve")
	void SetCurveValues(TArray<FVector2D> NewValues);

	UFUNCTION(BlueprintCallable, Category = "DynamicCurve")
	static UDynamicFloatCurve* CreateDynamicCurve(UObject* Outer, TArray<FVector2D> InputKey);
};
