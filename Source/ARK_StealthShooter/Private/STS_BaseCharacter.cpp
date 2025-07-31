// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Weapon/STS_Weapon.h"
#include "Components/STS_HealthComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ASTS_BaseCharacter::ASTS_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<USTS_HealthComponent>(TEXT("HealthComponent"));

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	bIsMeleeAttacking = false;
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

	AnimInstance = GetMesh()->GetAnimInstance();
	if (IsValid(AnimInstance))
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &ASTS_BaseCharacter::StopMelee);
	}

	if (IsValid(HealthComponent))
	{
		HealthComponent->OnHealthChangedDelegate.AddDynamic(this, &ASTS_BaseCharacter::OnHealthChanged);
		HealthComponent->OnDeathDelegate.AddDynamic(this, &ASTS_BaseCharacter::OnDeath);
	}
}

void ASTS_BaseCharacter::StartMelee()
{
	if (bIsMeleeAttacking)
	{
		return;
	}

	if (AnimInstance != nullptr && MeleeMontage != nullptr)
	{
		bIsMeleeAttacking = true;
		GetMovementComponent()->StopMovementImmediately();
		AnimInstance->Montage_Play(MeleeMontage);
	}
	
}

void ASTS_BaseCharacter::StopMelee(UAnimMontage* AnimMontage, bool bInterrumped)
{
	if (AnimMontage == MeleeMontage)
	{
		bIsMeleeAttacking = false;
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

void ASTS_BaseCharacter::DoMeleeAttack()
{
	const FVector MeleeAttackLocation = GetMesh()->GetSocketLocation(MeleeSocketName);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	TArray<AActor*> OutActors;

	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), MeleeAttackLocation, MeleeAttackRange, MeleeObjectTypes, AActor::StaticClass(), ActorsToIgnore, OutActors))
	{
		AActor* HitActor = OutActors[0];
		if (IsValid(HitActor))
		{
			USTS_HealthComponent* HitActorHealthComponent = Cast<USTS_HealthComponent>(HitActor->GetComponentByClass(USTS_HealthComponent::StaticClass()));
			if (IsValid(HitActorHealthComponent))
			{
				HitActorHealthComponent->Kill(GetController(), this);
			}
		}
	}
}

void ASTS_BaseCharacter::Jump()
{
	Super::Jump();
}

void ASTS_BaseCharacter::StopJumping()
{
	Super::StopJumping();
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