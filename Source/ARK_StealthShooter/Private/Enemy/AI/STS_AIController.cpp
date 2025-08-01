// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/STS_AIController.h"
#include "Components/STS_HealthComponent.h"

ETeamAttitude::Type ASTS_AIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const AActor* OtherActor = &Other;
	return (USTS_HealthComponent::bIsFriendly(GetPawn(), OtherActor)) ? ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}
