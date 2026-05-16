// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPrototype/Public/Player/GASP_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GASPrototype/Public/Character/GASP_BaseCharacter.h"


void AGASP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Local PlayerSubsystem
	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(LocalPlayerSubsystem)) return;

	for (UInputMappingContext* InputMappingContext : InputMappingContexts)
	{
		LocalPlayerSubsystem->AddMappingContext(InputMappingContext, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;


	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
}

void AGASP_PlayerController::Jump()
{
	if (!IsValid(GetCharacter()) || !IsAlive()) return;
	GetCharacter()->Jump();
}

void AGASP_PlayerController::StopJumping()
{
	if (!IsValid(GetCharacter()) || !IsAlive()) return;
	GetCharacter()->StopJumping();
}

void AGASP_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn()) || !IsAlive()) return;

	const FVector2d MovementVector = Value.Get<FVector2D>();

	//using camera as forward direction
	const FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void AGASP_PlayerController::Look(const FInputActionValue& Value)
{
	if (!IsAlive()) return;

	const FVector2d LookVector = Value.Get<FVector2D>();
	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}

bool AGASP_PlayerController::IsAlive() const
{
	return true;
}
