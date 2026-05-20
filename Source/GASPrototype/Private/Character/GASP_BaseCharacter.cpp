// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPrototype/Public/Character/GASP_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTags/GASP_StateTags.h"


AGASP_BaseCharacter::AGASP_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* AGASP_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AGASP_BaseCharacter::GiveStartupAbilities()
{
	for (auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

void AGASP_BaseCharacter::ActivateAbility(const FGameplayTag& PrimaryTag,
                                          const FGameplayTag& SecondaryTag)
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent)) return;

	if (AbilitySystemComponent->TryActivateAbilitiesByTag(PrimaryTag.GetSingleTagContainer())) return;

	if (SecondaryTag.IsValid())
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag(SecondaryTag.GetSingleTagContainer());
	}
}

bool AGASP_BaseCharacter::IsMovementBlocked() const
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent)) return false;

	return AbilitySystemComponent->HasMatchingGameplayTag(GASPTags::States::Movement::InputBlocked);
}
