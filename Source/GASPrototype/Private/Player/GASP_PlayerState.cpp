// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GASP_PlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GASP_AbilitySystemComponent.h"
#include "AbilitySystem/GASP_AttributeSet.h"

AGASP_PlayerState::AGASP_PlayerState()
{
	//Raise PlayerState net update frequency, necessary to use GAS here. The default value is 1. 
	NetUpdateFrequency = 100.f;
	
	AbilitySystemComponent = CreateDefaultSubobject<UGASP_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed); //minimal replication necessary for Owner (this class)
	
	AttributeSet = CreateDefaultSubobject<UGASP_AttributeSet>(TEXT("AttributeSet"));
	
	
}

UAbilitySystemComponent* AGASP_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGASP_PlayerState::SetSelectedCharacterTag(FGameplayTag CharacterTag)
{
	SelectedCharacterTag = CharacterTag;
}

FGameplayTag AGASP_PlayerState::GetSelectedCharacterTag() const
{
	return SelectedCharacterTag;
}
