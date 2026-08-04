// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASP_EnemyCharacter.h"

#include "AbilitySystem/GASP_AbilitySystemComponent.h"
#include "AbilitySystem/GASP_AttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"


AGASP_EnemyCharacter::AGASP_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UGASP_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); // for npcs we use minimal

	AttributeSet = CreateDefaultSubobject<UGASP_AttributeSet>(TEXT("AttributeSet"));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
}

void AGASP_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent())) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);

	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());

	if (!HasAuthority()) return; // server only ↓

	GiveStartupAbilities();
	InitializeAttributes();

	UGASP_AttributeSet* GAS_AttributeSet = Cast<UGASP_AttributeSet>(GetAttributeSet());
	if (!IsValid(GAS_AttributeSet)) return;
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GAS_AttributeSet->GetHealthAttribute()).
	                             AddUObject
	                             (this, &ThisClass::OnHealthChanged);
}

void AGASP_EnemyCharacter::HandleDeath()
{
	Super::HandleDeath();
	OnDied.Broadcast();
}

void AGASP_EnemyCharacter::ResetAttributes()
{
	Super::ResetAttributes();
	OnRespawn.Broadcast();
}

UAbilitySystemComponent* AGASP_EnemyCharacter::GetAbilitySystemComponent() const
{
	if (!IsValid(AbilitySystemComponent)) return nullptr;
	return AbilitySystemComponent;
}

UAttributeSet* AGASP_EnemyCharacter::GetAttributeSet() const
{
	if (!IsValid(AttributeSet)) return nullptr;
	return AttributeSet;
}

void AGASP_EnemyCharacter::SetStartLocation(const FVector& NewStartPosition)
{
	StartLocation = NewStartPosition;
}
