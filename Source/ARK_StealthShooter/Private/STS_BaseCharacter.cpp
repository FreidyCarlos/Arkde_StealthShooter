// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Weapon/STS_Weapon.h"

// Sets default values
ASTS_BaseCharacter::ASTS_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
