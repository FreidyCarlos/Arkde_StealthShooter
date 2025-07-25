// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STS_Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "../ARK_StealthShooter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASTS_Weapon::ASTS_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	bIsDebug = false;

	ShotDistance = 10000.0f;
	ShotDamage = 20.0f;

	RoundsPerMinute = 600.0f;
}

// Called when the game starts or when spawned
void ASTS_Weapon::BeginPlay()
{
	Super::BeginPlay();	
	TimeBetweenShots = 60 / RoundsPerMinute;
}

void ASTS_Weapon::Fire()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();

		FVector TraceEnd = EyeLocation + (ShotDirection * ShotDistance);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FVector ImpactPoint = TraceEnd;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, WEAPON_COLLISION, QueryParams))
		{
			AActor* HitActor = Hit.GetActor();
			UGameplayStatics::ApplyDamage(HitActor, ShotDamage, MyOwner->GetInstigatorController(), MyOwner, DamageType);

			if (ImpactEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			}

			ImpactPoint = Hit.ImpactPoint;
		}

		if (MuzzleEffect)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, WeaponMesh, MuzzleSocketName);
		}

		if (TracerEffect)
		{
			UParticleSystemComponent* TracerComponent = UGameplayStatics::SpawnEmitterAttached(TracerEffect, WeaponMesh, MuzzleSocketName);
			if (TracerComponent)
			{
				TracerComponent->SetVectorParameter(TracerTargetName, ImpactPoint);
			}
		}

		if (bIsDebug)
		{
			DrawDebugLine(GetWorld(), EyeLocation, Hit.ImpactPoint, FColor::White, false, 1.0f, 0, 1.0f);
		}

		LastFireTime = GetWorld()->TimeSeconds;
	}
}

void ASTS_Weapon::StartFire()
{
	float FirstDelay = FMath::Max(0.0f, LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds);
	GetWorldTimerManager().SetTimer(TimerHandle_AutoFire, this, &ASTS_Weapon::Fire, TimeBetweenShots, true, FirstDelay);
}

void ASTS_Weapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_AutoFire);
}
