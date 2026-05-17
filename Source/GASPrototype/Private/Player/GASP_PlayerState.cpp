// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GASP_PlayerState.h"

#include "AbilitySystemComponent.h"

AGASP_PlayerState::AGASP_PlayerState()
{
	//Raise PlayerState net update frequency, necessary to use GAS here. The default value is 1. 
	SetNetUpdateFrequency(100.f);  
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed); //minimal replication necessary for Owner (this class)
	
}

UAbilitySystemComponent* AGASP_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
