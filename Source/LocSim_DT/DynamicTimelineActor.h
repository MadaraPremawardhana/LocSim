// Fill out your copyright notice in the Description page of Project Settings.

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
    UFUNCTION(BlueprintCallable, Category = "Timeline")
    void AddToTimeline(UTimelineComponent* InTimeline, const TArray<float>& Keys, const TArray<float>& Values); 

private:
    UPROPERTY()
    UTimelineComponent* Timeline;   // Member variable to hold the Timeline
    UPROPERTY(EditAnywhere, Category = "Timeline")
    UCurveFloat* TimelineCurve ;      // Curve to use for the timeline

};
