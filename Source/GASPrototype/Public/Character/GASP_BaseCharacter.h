// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GASP_BaseCharacter.generated.h"

class UGameplayAbility;
class UGASP_GameplayAbility;
struct FGameplayTag;

UCLASS()
class GASPROTOTYPE_API AGASP_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASP_BaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void ActivateAbility (FGameplayTag AbilityTag);

protected:
	//virtual void BeginPlay() override;
	void GiveStartupAbilities();

private:
	UPROPERTY(EditDefaultsOnly, Category = "GASP|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities; //Abilities BPs, not Objects
};
