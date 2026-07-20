// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GASP_Attack.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Character/GASP_BaseCharacter.h"
#include "GameplayTags/GASP_EventTags.h"

void UGASP_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo,
                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// used just for the send hit react event and aplly damage
	if (HitActors.Num() > 0)
		HitActors.Empty();
}

// sends Hit React event and applies damage GE to hit actors.
void UGASP_Attack::SendHitReactEventAndApplyDamage(const FGameplayEventData& Payload,
                                                   const TSubclassOf<UGameplayEffect> DamageGE,
                                                   bool bOncePerTarget, TSubclassOf<UGameplayEffect> OnHitPowerChargeGE)
{
	if (!IsValid(Payload.Target)) return;

	if (bOncePerTarget)
	{
		if (HitActors.Contains(Payload.Target)) return;
		HitActors.Add(Payload.Target);
	}

	// checks
	const AGASP_BaseCharacter* TargetCharacter = Cast<AGASP_BaseCharacter>(Payload.Target);
	if (!IsValid(TargetCharacter)) return;
	UAbilitySystemComponent* TargetASC = TargetCharacter->GetAbilitySystemComponent();
	if (!IsValid(TargetASC)) return;
	
	// sending hit react event
	const FGameplayTag& EventTag = GASPTags::Events::HitReact;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetASC->GetOwner(), EventTag, Payload);

	// Gameplay Effects
	UAbilitySystemComponent* AvatarASC = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(AvatarASC)) return;
	
	// damage GE
	if (IsValid(DamageGE))
	{
		const FGameplayEffectSpecHandle SpecHandle = AvatarASC->MakeOutgoingSpec(
		DamageGE, 1.f, Payload.ContextHandle);
		if (SpecHandle.IsValid())
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
	
	// power charge GE
	if (IsValid(OnHitPowerChargeGE))
	{
		const FGameplayEffectSpecHandle PowerChargeSpecHandle = AvatarASC->MakeOutgoingSpec(
			OnHitPowerChargeGE, 1.f, Payload.ContextHandle);
		if (PowerChargeSpecHandle.IsValid())
		{
			AvatarASC->ApplyGameplayEffectSpecToSelf(*PowerChargeSpecHandle.Data.Get());
		}
	}
}
