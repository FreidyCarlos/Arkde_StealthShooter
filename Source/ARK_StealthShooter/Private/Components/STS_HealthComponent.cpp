// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STS_HealthComponent.h"

// Sets default values for this component's properties
USTS_HealthComponent::USTS_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	DefaultHealth = 100.0f;
	bIsDead = false;
}

// Called when the game starts
void USTS_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = DefaultHealth;

	AActor* ActorOwner = GetOwner();
	if (IsValid(ActorOwner))
	{
		ActorOwner->OnTakeAnyDamage.AddDynamic(this, &USTS_HealthComponent::HandleTakeAnyDamage);
	}
}

void USTS_HealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f || bIsDead)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, DefaultHealth);
	OnHealthChangedDelegate.Broadcast(this, CurrentHealth, Damage, DamageType, InstigatedBy, DamageCauser);

	if (CurrentHealth == 0.0f)
	{
		bIsDead = true;
		OnDeathDelegate.Broadcast(this, InstigatedBy, DamageCauser);
	}
}

void USTS_HealthComponent::Kill(AController* InstigatedBy, AActor* DamageCauser)
{
	if (bIsDead)
	{
		return;
	}

	CurrentHealth = 0.0f;
	bIsDead = true;
	OnDeathDelegate.Broadcast(this, InstigatedBy, DamageCauser);
}
