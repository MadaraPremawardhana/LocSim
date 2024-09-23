#include "DynamicTimelineActor.h"

ADynamicTimelineActor::ADynamicTimelineActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create and initialize the Timeline component
    TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
  
}

void ADynamicTimelineActor::BeginPlay()
{
    Super::BeginPlay();
}

void ADynamicTimelineActor::AddToTimeline(UTimelineComponent* Timeline, float Time, float Value)
{
    if (Timeline)
    {
        // Example logic to add time and value to the timeline
        // In a real scenario, you'd need to define how you're adding values
        // This is just a placeholder for demonstration purposes

        // Get the current length of the timeline
        float CurrentLength = Timeline->GetTimelineLength();

        // Extend the timeline if the new time exceeds the current length
        if (Time > CurrentLength)
        {
            Timeline->SetTimelineLength(Time);
        }

        // Add a new track or update the value at the specified time
        // This would depend on how your timeline is set up
        // For example, using float tracks, etc.

        // Here, you can use a custom function to set the values at specified time
        // This needs to be implemented based on your timeline setup
    }
}
