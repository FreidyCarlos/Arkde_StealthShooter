// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "STS_EnvQueryHealAreaStatus.generated.h"

/**
 * 
 */
UCLASS()
class ARK_STEALTHSHOOTER_API USTS_EnvQueryHealAreaStatus : public UEnvQueryTest
{
	GENERATED_BODY()
	
public:

	USTS_EnvQueryHealAreaStatus(const FObjectInitializer& ObjectInitializer);

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;

	virtual FText GetDescriptionDetails() const override;
};
