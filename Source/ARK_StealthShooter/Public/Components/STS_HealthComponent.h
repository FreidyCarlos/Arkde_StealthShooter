// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STS_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, USTS_HealthComponent*, HealthComp, float, Health, float, HealthDelta, const UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDeathSignature, USTS_HealthComponent*, HealthComp, class AController*, InstigatedBy, AActor*, Killer);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARK_STEALTHSHOOTER_API USTS_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTS_HealthComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float DefaultHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;

public:

	UPROPERTY(BlueprintReadOnly)
	bool bIsDead;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeathDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:

	UFUNCTION(BlueprintCallable)
	bool IsDead() const {return bIsDead; };

	UFUNCTION(BlueprintCallable)
	void Kill(AController* InstigatedBy, AActor* DamageCauser);
};
