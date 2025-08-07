// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicFloatCurve.h"


void UDynamicFloatCurve::SetCurveValues(TArray<FVector2D> NewValues) {
	FloatCurve.Keys.Empty();
	for (FVector2D Key : NewValues) {
		FloatCurve.AddKey(Key.X, Key.Y);
	}

}

UDynamicFloatCurve* UDynamicFloatCurve::CreateDynamicCurve(UObject* Outer, TArray<FVector2D> InputKeys) {
	UDynamicFloatCurve* NewCurve = NewObject<UDynamicFloatCurve>(Outer, UDynamicFloatCurve::StaticClass());
	NewCurve->SetCurveValues(InputKeys);
	return NewCurve;
}