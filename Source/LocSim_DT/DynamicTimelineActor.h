#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "DynamicTimelineActor.generated.h"

UCLASS()
class LOCSIM_DT_API ADynamicTimelineActor : public AActor
{
    GENERATED_BODY()

public:
    ADynamicTimelineActor();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "Timeline")
    void AddToTimeline(UTimelineComponent* Timeline, float Time, float Value);

private:
    UPROPERTY()
    UTimelineComponent* TimelineComponent;
};
