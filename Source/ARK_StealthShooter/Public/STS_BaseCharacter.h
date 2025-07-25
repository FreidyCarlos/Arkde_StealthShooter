// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STS_BaseCharacter.generated.h"

class ASTS_Weapon;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTS_BaseCharacter();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTS_Weapon> startingWeaponClass;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	ASTS_Weapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponSocketName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();
};
