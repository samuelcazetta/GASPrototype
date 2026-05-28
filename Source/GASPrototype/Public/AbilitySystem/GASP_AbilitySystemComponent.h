// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GASP_AbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GASPROTOTYPE_API UGASP_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UGASP_AbilitySystemComponent();

protected:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRep_ActivateAbilities() override;
public:
private:
	//If ability has 'Activate On Given' tag, already activates it
	void HandleActivateAbilities(const FGameplayAbilitySpec& AbilitySpec );
	
	 
};
