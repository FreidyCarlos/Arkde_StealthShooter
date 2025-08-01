// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEQS/STS_EnvQueryHealAreaStatus.h"
#include "HealingArea/STS_HealingArea.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

USTS_EnvQueryHealAreaStatus::USTS_EnvQueryHealAreaStatus(const FObjectInitializer& ObjectInitializer)
{
	ValidItemType = UEnvQueryItemType_Actor::StaticClass();
}

void USTS_EnvQueryHealAreaStatus::RunTest(FEnvQueryInstance& QueryInstance) const
{
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		ASTS_HealingArea* HealingArea = Cast<ASTS_HealingArea>(GetItemActor(QueryInstance, It.GetIndex()));
		
		float Score = 0.0;

		if (HealingArea)
		{
			Score = HealingArea->bIsActive ? 1.0f : 0.0f;

			It.SetScore(TestPurpose, FilterType, Score, 0.0f, 1.0f);

			It.ForceItemState(HealingArea->bIsActive ? EEnvItemStatus::Passed : EEnvItemStatus::Failed);
		}
	}
}

FText USTS_EnvQueryHealAreaStatus::GetDescriptionTitle() const
{
	FString DescriptionTitle = "Testing for healing area status";
	return FText().FromString(DescriptionTitle);
}

FText USTS_EnvQueryHealAreaStatus::GetDescriptionDetails() const
{
	FString Description = "Score when active : 1, Score when inactive : 0";
	return FText().FromString(Description);
}