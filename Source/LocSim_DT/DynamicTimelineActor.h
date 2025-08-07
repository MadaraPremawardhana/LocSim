#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
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
    // The main function you'll call from Blueprint
    UFUNCTION(BlueprintCallable, Category = "Timeline")
    void SetDynamicTimeline(UTimelineComponent* Timeline, const TArray<float>& Keys, const TArray<float>& Values);

    UFUNCTION()
    void OnTimelineUpdate(float Value);

private:
    // Must be UPROPERTY to avoid garbage collection
    UPROPERTY()
    UCurveFloat* RuntimeCurve;
};
