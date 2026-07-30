// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GASP_SpecialAttack.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"

void UGASP_SpecialAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(ASC)) return;
	
	if (IsLocallyControlled() && IsValid(SpecialActivationCue))
	{
		UGameplayStatics::PlaySound2D(ASC, SpecialActivationCue);
	}
}
