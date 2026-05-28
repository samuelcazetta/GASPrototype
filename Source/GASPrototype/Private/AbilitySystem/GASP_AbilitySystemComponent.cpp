// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GASP_AbilitySystemComponent.h"

#include "GameplayTags/GASP_AbilityTags.h"


UGASP_AbilitySystemComponent::UGASP_AbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGASP_AbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);

	HandleActivateAbilities(AbilitySpec);
}

void UGASP_AbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	FScopedAbilityListLock AbilityListLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		HandleActivateAbilities(AbilitySpec);
	}
}

void UGASP_AbilitySystemComponent::HandleActivateAbilities(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!IsValid(AbilitySpec.Ability)) return;
	for (FGameplayTagContainer TagContainer = AbilitySpec.Ability->GetAssetTags(); auto Tag : TagContainer)
	{
		if (Tag.MatchesTagExact(GASPTags::Abilities::ActivateOnGiven))
		{
			TryActivateAbility(AbilitySpec.Handle);
			//GiveAbilityAndActivateOnce() -> could be this but we want the ability to continue activated.
			return;
		}
	}
}
