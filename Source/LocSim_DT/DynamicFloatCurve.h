#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "DynamicFloatCurve.generated.h"

UCLASS(BlueprintType)
class LOCSIM_DT_API UDynamicFloatCurve : public UCurveFloat
{
    GENERATED_BODY()

public:
    // Sets new key/value pairs on the curve
    UFUNCTION(BlueprintCallable, Category = "Dynamic Curve")
    void SetCurveValues(const TArray<FVector2D>& NewValues);

    // Static function to create a runtime float curve from key/value pairs
    UFUNCTION(BlueprintCallable, Category = "Dynamic Curve")
    static UDynamicFloatCurve* CreateDynamicCurve(UObject* Outer, const TArray<FVector2D>& InputKeys);

    // Save this curve to disk at a given path (e.g., "Blueprints/Alpha")
    UFUNCTION(BlueprintCallable, Category = "Dynamic Curve|Editor Only")
    bool SaveCurveToDisk(const FString& AssetPath);

};
