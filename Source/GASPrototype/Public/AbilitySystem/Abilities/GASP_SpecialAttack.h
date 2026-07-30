// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagsManager.h"
#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GASP_Attack.h"
#include "GASP_SpecialAttack.generated.h"

class UPostProcessComponent;
/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API UGASP_SpecialAttack : public UGASP_Attack
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASP|Abilities")
	TObjectPtr<USoundBase> SpecialActivationCue;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
