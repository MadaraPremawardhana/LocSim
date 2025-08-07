#include "DynamicTimelineActor.h"

ADynamicTimelineActor::ADynamicTimelineActor()
{
    FName TimelineName(TEXT("TrainMover"));
    UTimelineComponent* FoundTimeline = FindComponentByClass<UTimelineComponent>();
    Timeline = FoundTimeline;
}

void ADynamicTimelineActor::BeginPlay()
{
    Super::BeginPlay();
}

void ADynamicTimelineActor::AddToTimeline(UTimelineComponent* InTimeline, const TArray<float>& Keys, const TArray<float>& Values)
{

    if (!InTimeline)  // Check if InTimeline is valid
    {
        UE_LOG(LogTemp, Warning, TEXT("InTimeline is null!"));
        return;
    }

    //TimelineCurve = ConstructorHelpers::FObjectFinder<UCurveFloat> CurveAsset(TEXT("CurveFloat'/Game/Blueprints/Train.AlphaCurve.AlphaCurve'"));

    if (!TimelineCurve)  // Check if TimelineCurve is valid
    {
        UE_LOG(LogTemp, Warning, TEXT("TimelineCurve is null!"));
        return;
    }

    // Clear existing tracks
    InTimeline->SetFloatCurve(nullptr, FName(TEXT("Alpha")));   // Clears the float track
    InTimeline->SetTimelineFinishedFunc(FOnTimelineEvent());         // Clears the event track

    // Ensure Keys and Values have the same length
    if (Keys.Num() != Values.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("Keys and Values arrays must have the same length."));
        return;
    }

    // Check if there are any keys to add
    if (Keys.Num() == 0)
    {
        return; // No keys provided
    }

    // Initialize the curve with a starting key if needed
    TimelineCurve->FloatCurve.AddKey(0.0f, 0.0f);

    // Add the keys and values to the timeline
    for (int32 i = 0; i < Keys.Num(); ++i)
    {
        // Add key to the curve
        TimelineCurve->FloatCurve.AddKey(Keys[i], Values[i]);

        // Create a timeline callback for the current timeline
        FOnTimelineFloat TimelineCallback;
        TimelineCallback.BindUFunction(this, FName("TimelineFloatReturn"));

        // This will add the curve to the timeline
        InTimeline->AddInterpFloat(TimelineCurve, TimelineCallback);
    }

    // Set the total length of the timeline to the last key
    float LastKey = Keys[Keys.Num() - 1];
    InTimeline->SetTimelineLength(LastKey);
}


