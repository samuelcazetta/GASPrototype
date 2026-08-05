// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPrototype/Public/Player/GASP_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/GameModeBase.h"
#include "GameInstance/GASP_AdvancedFriendsGameInstance.h"
#include "GameMode/GASP_GameMode.h"
#include "GameplayTags/GASP_AbilityTags.h"
#include "GASPrototype/Public/Character/GASP_BaseCharacter.h"
#include "Player/GASP_PlayerState.h"


void AGASP_PlayerController::Server_SetSelectedCharacterTag_Implementation(const FGameplayTag SelectedCharacterTag)
{
	if (!SelectedCharacterTag.IsValid()) return;

	AGASP_PlayerState* PS = GetPlayerState<AGASP_PlayerState>();
	if (!IsValid(PS)) return;

	PS->SetSelectedCharacterTag(SelectedCharacterTag);

	AGASP_GameMode* GameMode = Cast<AGASP_GameMode>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode)) return;

	GameMode->ResetASC(PS->GetAbilitySystemComponent());

	if (APawn* CurrentPawn = GetPawn())
	{
		UnPossess();
		CurrentPawn->Destroy();
	}

	GameMode->RestartPlayer(this);
}

void AGASP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	//Local PlayerSubsystem
	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(LocalPlayerSubsystem)) return;

	//Add all Mapping Contexts
	for (UInputMappingContext* InputMappingContext : InputMappingContexts)
	{
		LocalPlayerSubsystem->AddMappingContext(InputMappingContext, 0);
	}

	//Bind all Input Actions
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;

	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ThisClass::Look);

	EnhancedInputComponent->BindAction(AttackInputAction, ETriggerEvent::Started, this, &ThisClass::Attack);
	EnhancedInputComponent->BindAction(DashInputAction, ETriggerEvent::Started, this, &ThisClass::Dash);
	EnhancedInputComponent->BindAction(SpecialInputAction, ETriggerEvent::Started, this, &ThisClass::Special);
}

void AGASP_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	BaseCharacter = Cast<AGASP_BaseCharacter>(InPawn);
}

void AGASP_PlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	BaseCharacter = Cast<AGASP_BaseCharacter>(GetPawn());
}

void AGASP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController()) return;
	UGASP_AdvancedFriendsGameInstance* GI = Cast<UGASP_AdvancedFriendsGameInstance>(GetGameInstance());
	if (!IsValid(GI)) return;

	if (!GI->SelectedCharacterTag.IsValid()) return;
	Server_SetSelectedCharacterTag(GI->SelectedCharacterTag);
}

void AGASP_PlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	BaseCharacter = nullptr;
}

void AGASP_PlayerController::Jump()
{
	if (!IsValid(BaseCharacter) || !IsAlive()) return;
	BaseCharacter->Jump();
}

void AGASP_PlayerController::StopJumping()
{
	if (!IsValid(BaseCharacter) || !IsAlive()) return;
	BaseCharacter->StopJumping();
}

void AGASP_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(BaseCharacter) || !IsAlive()) return;
	if (BaseCharacter->IsMovementBlocked()) return;
	
	const FVector2d MovementVector = Value.Get<FVector2D>();

	//using camera as forward direction
	const FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	BaseCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
	BaseCharacter->AddMovementInput(RightDirection, MovementVector.X);
}

void AGASP_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2d LookVector = Value.Get<FVector2D>();
	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}

void AGASP_PlayerController::Attack()
{
	if (!IsValid(BaseCharacter) || !IsAlive()) return;
	BaseCharacter->ActivateAbility(GASPTags::Abilities::Attack, GASPTags::Abilities::AttackContinue);
}

void AGASP_PlayerController::Special()
{
	if (!IsValid(BaseCharacter) || !IsAlive()) return;
	BaseCharacter->ActivateAbility(GASPTags::Abilities::Special);
	
}

void AGASP_PlayerController::Dash()
{
	if (!IsValid(BaseCharacter) || !IsAlive()) return;
	BaseCharacter->ActivateAbility(GASPTags::Abilities::Dash);
}

bool AGASP_PlayerController::IsAlive() const
{
	return IsValid(BaseCharacter) && BaseCharacter->IsAlive();
}
