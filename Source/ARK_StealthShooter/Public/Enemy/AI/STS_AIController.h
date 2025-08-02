// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STS_AIController.generated.h"

/**
 * 
 */
UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_AIController : public AAIController
{
	GENERATED_BODY()

	ASTS_AIController(const FObjectInitializer& ObjectInitializer);

	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
};
