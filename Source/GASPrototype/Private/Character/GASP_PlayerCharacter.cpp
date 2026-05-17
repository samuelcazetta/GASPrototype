// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASP_PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/GASP_PlayerState.h"


// Sets default values
AGASP_PlayerCharacter::AGASP_PlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//SpringArm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 600.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	//Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	//Character
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//MovementComponent setup
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1080.0f, 0.0f);
	GetCharacterMovement()->MaxAcceleration = 8192.0f;
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

UAbilitySystemComponent* AGASP_PlayerCharacter::GetAbilitySystemComponent() const
{
	AGASP_PlayerState* GASPPlayerState = Cast<AGASP_PlayerState>(GetPlayerState());
	if (!IsValid(GASPPlayerState))return nullptr;

	return GASPPlayerState->GetAbilitySystemComponent();
}

void AGASP_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	//Initiating GAS on Server
	if (!IsValid(GetAbilitySystemComponent()) || !HasAuthority()) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	
	//Grant Startup Abilities
	GiveStartupAbilities();
}

void AGASP_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	//Initiating GAS on Client
	if (!IsValid(GetAbilitySystemComponent())) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
}


void AGASP_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Start with a slight camera rotation
	if (AController* PC = GetController())
	{
		PC->SetControlRotation(FRotator(-20.0f, GetActorRotation().Yaw, 0.0f));
	}
}
