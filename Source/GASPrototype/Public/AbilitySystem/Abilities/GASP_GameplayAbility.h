// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GASP_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API UGASP_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASP|Abilities")
	bool bAbilityEnabled = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASP|Debug")
	bool bEnableDebug = false;
};
