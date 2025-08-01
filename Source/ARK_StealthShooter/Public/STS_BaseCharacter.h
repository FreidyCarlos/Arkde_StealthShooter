// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STS_BaseCharacter.generated.h"

class ASTS_Weapon;
class USTS_HealthComponent;
class UPawnNoiseEmitterComponent;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTS_BaseCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health Component")
	USTS_HealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Noise Component")
	UPawnNoiseEmitterComponent* CharacterNoiseEmitter;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTS_Weapon> startingWeaponClass;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	ASTS_Weapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	FName MeleeSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float MeleeAttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	UAnimMontage* MeleeMontage;

	UAnimInstance* AnimInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	TArray<TEnumAsByte<EObjectTypeQuery>> MeleeObjectTypes;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsMeleeAttacking;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartMelee();

	UFUNCTION(BlueprintCallable)
	void StopMelee(UAnimMontage* AnimMontage, bool bInterrumped);

public:

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable)
	void DoMeleeAttack();

	void Jump();

	void StopJumping();

	UFUNCTION()
	void OnHealthChanged(USTS_HealthComponent* HealthComp, float Health, float HealthDelta, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnDeath(USTS_HealthComponent* HealthComp, class AController* InstigatedBy, AActor* Killer);

	UFUNCTION()
	void CharacterMakeNoise(const float Loudness, const FVector NoiseLocation);
};
