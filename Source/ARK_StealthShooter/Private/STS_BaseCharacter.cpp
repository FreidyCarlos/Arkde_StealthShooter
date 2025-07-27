// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Weapon/STS_Weapon.h"
#include "Components/STS_HealthComponent.h"

// Sets default values
ASTS_BaseCharacter::ASTS_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<USTS_HealthComponent>(TEXT("HealthComponent"));


	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

// Called when the game starts or when spawned
void ASTS_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(startingWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<ASTS_Weapon>(startingWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocketName);
		}
	}

	if (IsValid(HealthComponent))
	{
		HealthComponent->OnHealthChangedDelegate.AddDynamic(this, &ASTS_BaseCharacter::OnHealthChanged);
		HealthComponent->OnDeathDelegate.AddDynamic(this, &ASTS_BaseCharacter::OnDeath);
	}
}

void ASTS_BaseCharacter::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}
}

void ASTS_BaseCharacter::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
	}
}

void ASTS_BaseCharacter::OnHealthChanged(USTS_HealthComponent* HealthComp, float Health, float HealthDelta, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{

}

void ASTS_BaseCharacter::OnDeath(USTS_HealthComponent* HealthComp, class AController* InstigatedBy, AActor* Killer)
{
	StopFire();
	GetMovementComponent()->StopMovementImmediately();
	this->SetActorEnableCollision(false);
	HealthComponent->OnHealthChangedDelegate.RemoveDynamic(this, &ASTS_BaseCharacter::OnHealthChanged);
	HealthComponent->OnDeathDelegate.RemoveDynamic(this, &ASTS_BaseCharacter::OnDeath);
}