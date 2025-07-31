// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STS_BaseCharacter.h"
#include "STS_Enemy.generated.h"

class ASTS_PatrolActor;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_Enemy : public ASTS_BaseCharacter
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol")
	ASTS_PatrolActor* PatrolActorReference;
};
