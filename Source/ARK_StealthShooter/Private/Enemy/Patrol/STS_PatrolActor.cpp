#include "Enemy/Patrol/STS_PatrolActor.h"
#include "Components/SplineComponent.h"

// Sets default values
ASTS_PatrolActor::ASTS_PatrolActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

// Called when the game starts or when spawned
void ASTS_PatrolActor::BeginPlay()
{
	Super::BeginPlay();
}

FVector ASTS_PatrolActor::GetWorldLocationByIndex(const int32 Index) const
{
	if (SplineComponent && Index <= GetLastIndex())
	{
		return SplineComponent->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
	}

	return GetActorLocation();
}

int32 ASTS_PatrolActor::GetLastIndex() const
{
	if (SplineComponent)
	{
		return SplineComponent->GetNumberOfSplinePoints();
	}

	return 0;
}