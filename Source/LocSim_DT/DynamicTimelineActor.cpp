#include "DynamicTimelineActor.h"

ADynamicTimelineActor::ADynamicTimelineActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADynamicTimelineActor::BeginPlay()
{
    Super::BeginPlay();
}

void ADynamicTimelineActor::SetDynamicTimeline(UTimelineComponent* Timeline, const TArray<float>& Keys, const TArray<float>& Values)
{
    if (!IsValid(Timeline))
    {
        UE_LOG(LogTemp, Error, TEXT("Timeline is null or invalid."));
        return;
    }

    if (Keys.Num() != Values.Num() || Keys.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Keys and values must match and not be empty."));
        return;
    }

    // Create runtime curve (must be UPROPERTY to avoid GC)
    RuntimeCurve = NewObject<UCurveFloat>(this);
    if (!RuntimeCurve)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create dynamic curve."));
        return;
    }

    // Clear any previous keys
    RuntimeCurve->FloatCurve.Reset();

    // Add keys to the curve
    for (int32 i = 0; i < Keys.Num(); ++i)
    {
        RuntimeCurve->FloatCurve.AddKey(Keys[i], Values[i]);
    }

    // Clear old track and setup new one
    Timeline->Stop();
    Timeline->SetPlaybackPosition(0.0f, false);
    Timeline->SetLooping(false);
    Timeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

    FOnTimelineFloat TimelineUpdate;
    TimelineUpdate.BindUFunction(this, FName("OnTimelineUpdate"));

    // Remove old curves — not officially exposed, so we overwrite
    Timeline->AddInterpFloat(RuntimeCurve, TimelineUpdate, FName("DynamicTrack"));

    Timeline->PlayFromStart();

    UE_LOG(LogTemp, Log, TEXT("Dynamic timeline started."));
}

void ADynamicTimelineActor::OnTimelineUpdate(float Value)
{
    UE_LOG(LogTemp, Log, TEXT("Timeline update value: %f"), Value);
}
