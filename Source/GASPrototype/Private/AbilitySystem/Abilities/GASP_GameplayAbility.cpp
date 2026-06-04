// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GASP_GameplayAbility.h"

#include "AbilitySystemComponent.h"

void UGASP_GameplayAbility::RemoveMatchingLooseTags(FGameplayTagContainer LooseTags)
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(AbilitySystemComponent)) return;

	for (auto LooseTag : LooseTags)
	{
		if (AbilitySystemComponent->HasMatchingGameplayTag(LooseTag))
		{
			AbilitySystemComponent->RemoveLooseGameplayTag(LooseTag);
		}
	}
}
