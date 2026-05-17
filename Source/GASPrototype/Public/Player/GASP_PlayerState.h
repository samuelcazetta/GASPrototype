// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GASP_PlayerState.generated.h"

class UAbilitySystemComponent;

UCLASS()
class GASPROTOTYPE_API AGASP_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AGASP_PlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
private:
	UPROPERTY(VisibleAnywhere, Category = "GASP|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
};
