// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STS_Weapon.generated.h"

class UStaticMeshComponent;
class UParticleSystem;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_Weapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTS_Weapon();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	FName TracerTargetName;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
	bool bIsDebug;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float ShotDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float ShotDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (Clampmin = 0.0f))
	float RoundsPerMinute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float TimeBetweenShots;

	float LastFireTime;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	FTimerHandle TimerHandle_AutoFire;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Fire();

public:

	void StartFire();

	void StopFire();
};
