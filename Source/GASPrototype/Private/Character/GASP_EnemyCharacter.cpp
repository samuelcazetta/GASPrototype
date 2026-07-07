// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASP_EnemyCharacter.h"

#include "AbilitySystem/GASP_AbilitySystemComponent.h"
#include "AbilitySystem/GASP_AttributeSet.h"


// Sets default values
AGASP_EnemyCharacter::AGASP_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UGASP_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); // remember, for npcs we use minimal
	
	AttributeSet = CreateDefaultSubobject<UGASP_AttributeSet>(TEXT("AttributeSet"));
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

void AGASP_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent())) return;

	//defining ASC Owner and Avatar 
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);

	// tell UI that ASC and attributes are initialized
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());

	if (!HasAuthority()) return; // server only ↓

	// startup abilities and attributes 
	GiveStartupAbilities();
	InitializeAttributes();

	//Consult if Enemy is alive every time health attribute changes
	UGASP_AttributeSet* GAS_AttributeSet = Cast<UGASP_AttributeSet>(GetAttributeSet());
	if (!IsValid(GAS_AttributeSet)) return;
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GAS_AttributeSet->GetHealthAttribute()).
	                             AddUObject 
	                             (this, &ThisClass::OnHealthChanged);
}
