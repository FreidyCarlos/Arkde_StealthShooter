// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STS_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASTS_PlayerCharacter::ASTS_PlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true; //Allows to assign the object to which the character's rotation reacts

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASTS_PlayerCharacter::MoveFoward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ASTS_PlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ASTS_PlayerCharacter::StartCrouch()
{
	Crouch();
}

void ASTS_PlayerCharacter::EndCrouch()
{
	UnCrouch();
}

void ASTS_PlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &ASTS_PlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookSide", this, &ASTS_PlayerCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAxis("MoveFoward", this, &ASTS_PlayerCharacter::MoveFoward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTS_PlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASTS_PlayerCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASTS_PlayerCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASTS_PlayerCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASTS_PlayerCharacter::StopFire);
}

FVector ASTS_PlayerCharacter::GetPawnViewLocation() const
{
	if (IsValid(CameraComponent))
	{
		return CameraComponent->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}
