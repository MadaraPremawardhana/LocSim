// DynamicTimelineActor.h
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
    virtual void Tick(float DeltaTime) override;

    // Timeline component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timeline")
    UTimelineComponent* Alpha;

    // The dynamic float curve used by timeline
    UPROPERTY()
    UCurveFloat* DynamicCurve;

    // Delegate for timeline update
    FOnTimelineFloat UpdateDelegate;

    // Function to apply the timeline data
    UFUNCTION(BlueprintCallable, Category = "Timeline")
    void ApplyDynamicTimeline(UTimelineComponent* Timeline, const TArray<FVector2D>& KeyValuePoints);

    UFUNCTION()
    void OnTimelineUpdate(float Value);
};
