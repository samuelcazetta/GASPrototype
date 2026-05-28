// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPrototype/Public/Character/GASP_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/GASP_AttributeSet.h"
#include "GameplayTags/GASP_StateTags.h"


AGASP_BaseCharacter::AGASP_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Forces bone updates even when not rendered (required for correct replication on dedicated servers).
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
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

void AGASP_BaseCharacter::InitializeAttributes()
{
	if(!IsValid(InitialAttributesEffect)) return;
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpec = GetAbilitySystemComponent()->MakeOutgoingSpec(InitialAttributesEffect, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
	
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
	const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent)) return false;

	return AbilitySystemComponent->HasMatchingGameplayTag(GASPTags::States::Movement::InputBlocked);
}

bool AGASP_BaseCharacter::IsAlive() const
{
	//todo: find a way to link attribute set without reference 
	//attribute set applies a tag death. IsAlive checks tag to return
	return true;
}
