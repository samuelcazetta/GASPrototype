// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "GASP_BaseCharacter.generated.h"

class UGameplayAbility;
class UGASP_GameplayAbility;

UCLASS()
class GASPROTOTYPE_API AGASP_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASP_BaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	/**
	 * This function implements a slight Hack 'n Slash like combo mechanic within GAS.
	 * Input starts or continues sequences:
	 * Tries primary ability (opener); falls back to secondary (combo chain) if primary fails.
	 * If no combo is intended, just PrimaryTag is needed.
	 * 
	 * @param PrimaryTag The primary gameplay tag for the ability.
	 * @param SecondaryTag The secondary gameplay tag for fallback ability. Only for combo Abilities.
	 */
	void ActivateAbility (const FGameplayTag& PrimaryTag, const FGameplayTag& SecondaryTag = FGameplayTag());
	
	bool IsMovementBlocked() const;

protected:
	//virtual void BeginPlay() override;
	void GiveStartupAbilities();

private:
	UPROPERTY(EditDefaultsOnly, Category = "GASP|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities; //Abilities BPs, not Objects
};
