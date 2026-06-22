// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPrototype/Public/Character/GASP_BaseCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/GASP_AttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTags/GASP_EventTags.h"
#include "GameplayTags/GASP_StateTags.h"


AGASP_BaseCharacter::AGASP_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Forces bone updates even when not rendered (required for correct replication on dedicated servers).
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	
	// little detail used to highlight character when Special Ability is cast.
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(1);
}

UAbilitySystemComponent* AGASP_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

UAttributeSet* AGASP_BaseCharacter::GetAttributeSet() const
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
	if (!IsValid(InitialAttributesEffect)) return;
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpec = GetAbilitySystemComponent()->MakeOutgoingSpec(
		InitialAttributesEffect, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
}

void AGASP_BaseCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue <= 0.f)
	{
		HandleDeath();
	}
}

void AGASP_BaseCharacter::HandleDeath()
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent)) return;
	
	FGameplayEventData Payload;
	//can insert any extra info here in Payload if necessary
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GASPTags::Events::Death, Payload);
	
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

void AGASP_BaseCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent)) return;
	
	//if landed
	if (PrevMovementMode == MOVE_Falling &&	GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		//if air-dashed, remove tag
		if (AbilitySystemComponent->HasMatchingGameplayTag(GASPTags::States::Movement::AirDashed))
		{
			AbilitySystemComponent->RemoveLooseGameplayTag(GASPTags::States::Movement::AirDashed);
		}
	}
}

bool AGASP_BaseCharacter::IsMovementBlocked() const
{
	const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent)) return false;

	return AbilitySystemComponent->HasMatchingGameplayTag(GASPTags::States::Movement::InputBlocked);
}

bool AGASP_BaseCharacter::IsTangible() const
{
	const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent)) return false;

	return !AbilitySystemComponent->HasMatchingGameplayTag(GASPTags::States::Intangible);
}

bool AGASP_BaseCharacter::IsAlive() const
{
	const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent)) return false;
	
	return !AbilitySystemComponent->HasMatchingGameplayTag(GASPTags::States::Dead);
}

void AGASP_BaseCharacter::ResetAttributes()
{
	InitializeAttributes();
}
