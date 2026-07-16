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
	if (HitActors.Num() > 0) HitActors.Empty();
}

// sends Hit React event and applies damage GE to hit actors.
void UGASP_Attack::SendHitReactEventAndApplyDamage(const FGameplayEventData& Payload,
                                                   const TSubclassOf<UGameplayEffect> DamageGE,
                                                   bool bOncePerTarget)
{
	if (!IsValid(Payload.Target)) return;
	
	if (bOncePerTarget)
	{
		if (HitActors.Contains(Payload.Target)) return;
		HitActors.Add(Payload.Target);
	}

	// sending hit react event
	const AGASP_BaseCharacter* TargetCharacter = Cast<AGASP_BaseCharacter>(Payload.Target);
	if (!IsValid(TargetCharacter)) return;
	
	UAbilitySystemComponent* TargetASC = TargetCharacter->GetAbilitySystemComponent();
	if (!IsValid(TargetASC)) return;
	const FGameplayTag& EventTag = GASPTags::Events::HitReact;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetASC->GetOwner(), EventTag, Payload);

	// sending damage GE
	const UAbilitySystemComponent* AvatarASC = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(AvatarASC)) return;
	const FGameplayEffectSpecHandle SpecHandle = AvatarASC->MakeOutgoingSpec(
		DamageGE, 1.f, Payload.ContextHandle);
	if (!SpecHandle.IsValid()) return;
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
