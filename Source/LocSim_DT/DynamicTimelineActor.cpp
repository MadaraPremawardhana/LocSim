// DynamicTimelineActor.cpp

#include "DynamicTimelineActor.h"

ADynamicTimelineActor::ADynamicTimelineActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADynamicTimelineActor::BeginPlay()
{
    Super::BeginPlay();

    // Find the Timeline component named "Alpha" that already exists
    Alpha = FindComponentByClass<UTimelineComponent>();

    if (!Alpha)
    {
        UE_LOG(LogTemp, Error, TEXT("Timeline component Alpha not found!"));
        return;
    }

    TArray<FVector2D> CurveKeys = {
        FVector2D(0.0f, 0.0f),
        FVector2D(1.0f, 100.0f),
        FVector2D(2.0f, 200.0f)
    };

    ApplyDynamicTimeline(Alpha, CurveKeys);
}

void ADynamicTimelineActor::ApplyDynamicTimeline(UTimelineComponent* Timeline, const TArray<FVector2D>& KeyValuePoints)
{
    if (!IsValid(Timeline))
    {
        UE_LOG(LogTemp, Error, TEXT("Timeline is invalid."));
        return;
    }

    if (KeyValuePoints.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No key/value data provided for timeline."));
        return;
    }

    // Create dynamic curve if not created yet
    if (!DynamicCurve)
    {
        DynamicCurve = NewObject<UCurveFloat>(this, TEXT("RuntimeCurve"));
    }

    if (!DynamicCurve)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create curve."));
        return;
    }

    // Clear previous keys
    DynamicCurve->FloatCurve.Reset();

    // Add keys from FVector2D array
    for (const FVector2D& Point : KeyValuePoints)
    {
        DynamicCurve->FloatCurve.AddKey(Point.X, Point.Y);
    }

    // Stop and reset timeline
    Timeline->Stop();
    Timeline->SetPlaybackPosition(0.0f, false);
    Timeline->SetLooping(false);
    Timeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

    // Unbind previous curve to prevent duplicates
    Timeline->SetFloatCurve(nullptr, FName("Alpha"));

    // Bind update function delegate once (store it persistently)
    UpdateDelegate.BindUFunction(this, FName("OnTimelineUpdate"));

    // Add float interpolation track with the track name "Alpha"
    Timeline->AddInterpFloat(DynamicCurve, UpdateDelegate, FName("Alpha"));

    Timeline->PlayFromStart();

    UE_LOG(LogTemp, Log, TEXT("Dynamic timeline started with %d keys."), KeyValuePoints.Num());
}

void ADynamicTimelineActor::OnTimelineUpdate(float Value)
{
    UE_LOG(LogTemp, Log, TEXT("Timeline Update: Value = %f"), Value);

    FVector NewLocation = GetActorLocation();
    NewLocation.X = Value; // Move actor on X axis based on timeline value
    SetActorLocation(NewLocation);
}

void ADynamicTimelineActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Alpha)
    {
        Alpha->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
    }
}
