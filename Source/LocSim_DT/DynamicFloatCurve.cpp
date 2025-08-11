#include "DynamicFloatCurve.h"

#include "UObject/Package.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/PackageName.h"
#include "UObject/SavePackage.h"

void UDynamicFloatCurve::SetCurveValues(const TArray<FVector2D>& NewValues)
{
    FloatCurve.Keys.Empty();

    for (const FVector2D& Key : NewValues)
    {
        FloatCurve.AddKey(Key.X, Key.Y);
    }

    FloatCurve.AutoSetTangents(0.0f); // Optional smoothing
    UE_LOG(LogTemp, Log, TEXT("SetCurveValues: %d keys added to curve."), NewValues.Num());
}

UDynamicFloatCurve* UDynamicFloatCurve::CreateDynamicCurve(UObject* Outer, const TArray<FVector2D>& InputKeys)
{
    UDynamicFloatCurve* NewCurve = NewObject<UDynamicFloatCurve>(Outer, UDynamicFloatCurve::StaticClass(), NAME_None, RF_Transient);

    if (NewCurve)
    {
        NewCurve->SetCurveValues(InputKeys);
    }

    return NewCurve;
}


#if WITH_EDITOR
bool UDynamicFloatCurve::SaveCurveToDisk(const FString& AssetPath)
{
    if (AssetPath.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("SaveCurveToDisk: AssetPath is empty."));
        return false;
    }

    // Ensure the path is a valid long package name
    FString PackageName = AssetPath;
    if (FPaths::GetExtension(PackageName) == TEXT("uasset"))
    {
        PackageName = FPaths::GetPath(PackageName) / FPaths::GetBaseFilename(PackageName);
    }
    if (!PackageName.StartsWith(TEXT("/")))
    {
        PackageName = TEXT("/") + PackageName;
    }
    if (!FPackageName::IsValidLongPackageName(PackageName))
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid package name: %s"), *PackageName);
        return false;
    }

    FString AssetName = FPackageName::GetShortName(PackageName);

    // Create the package
    UPackage* Package = CreatePackage(*PackageName);
    if (!Package)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create package: %s"), *PackageName);
        return false;
    }

    // Create a new curve object inside the package (not transient!)
    UDynamicFloatCurve* SavedCurve = NewObject<UDynamicFloatCurve>(
        Package,
        UDynamicFloatCurve::StaticClass(),
        *AssetName,
        RF_Public | RF_Standalone
    );

    // Copy our curve data into the saved object
    SavedCurve->FloatCurve = this->FloatCurve;

    // Mark dirty and register
    Package->MarkPackageDirty();
    FAssetRegistryModule::AssetCreated(SavedCurve);

    // Convert package path to file path
    FString FilePath = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

    // Save the package
    bool bSuccess = UPackage::SavePackage(
        Package,
        SavedCurve,
        EObjectFlags::RF_Public | EObjectFlags::RF_Standalone,
        *FilePath,
        GError,
        nullptr,
        false,
        true,
        SAVE_NoError
    );

    if (bSuccess)
    {
        UE_LOG(LogTemp, Log, TEXT("Successfully saved curve to %s"), *FilePath);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to save curve to %s"), *FilePath);
    }

    return bSuccess;
}
#endif

