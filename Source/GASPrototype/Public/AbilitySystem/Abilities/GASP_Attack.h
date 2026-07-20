// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASP_GameplayAbility.h"
#include "GASP_Attack.generated.h"

/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API UGASP_Attack : public UGASP_GameplayAbility
{
	GENERATED_BODY()

private:
	TArray<TObjectPtr<const AActor>> HitActors;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "GASP|Abilities")
	void SendHitReactEventAndApplyDamage(
		const FGameplayEventData& Payload,
		TSubclassOf<UGameplayEffect> DamageGE,
		bool bOncePerTarget = true,
		TSubclassOf<UGameplayEffect> OnHitPowerChargeGE = nullptr);
};
