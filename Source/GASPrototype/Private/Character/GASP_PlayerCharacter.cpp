// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASP_PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/GASP_PlayerController.h"


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
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f; 
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f; 
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f; 
}

// Called when the game starts or when spawned
void AGASP_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AController* PC = GetController())
	{
		PC->SetControlRotation(FRotator(-20.0f, GetActorRotation().Yaw, 0.0f));
	}
}
