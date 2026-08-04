// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GASP_SpecialAttack.h"
#include "AbilitySystemComponent.h"
#include "Character/GASP_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UGASP_SpecialAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGASP_SpecialAttack::PlaySpecialActivationSound() const
{
	if (!IsValid(SpecialActivationSound) || !IsValid(GetAvatarActorFromActorInfo())) return;
	UGameplayStatics::PlaySound2D(GetAvatarActorFromActorInfo(), SpecialActivationSound);
}

void UGASP_SpecialAttack::PlayFadePostProcess(const bool bFadeIn) const
{
	AGASP_PlayerCharacter* Player = Cast<AGASP_PlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!IsValid(Player) || !Player->IsLocallyControlled()) return;
	
	Player->SpecialAttackFade(bFadeIn);
}

void UGASP_SpecialAttack::PlayLocalActivationEffects() const
{
	if (!IsLocallyControlled()) return;
	
	PlaySpecialActivationSound();
	PlayFadePostProcess(true);
}

void UGASP_SpecialAttack::PlayLocalEndEffects() const
{
	if (!IsLocallyControlled()) return;
	PlayFadePostProcess(false);
}
