// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASP_GameplayAbility.h"
#include "GASP_RangedAttack.generated.h"

class AGASP_BaseCharacter;
/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API UGASP_RangedAttack : public UGASP_GameplayAbility
{
	GENERATED_BODY()
	
protected:
	/**
	 * Searches for nearby characters and returns the one with the highest forward alignment
	 * (dot product) above the specified threshold.
	 */
	UFUNCTION(BlueprintCallable, Category = "GASP|Abilities")
	AGASP_BaseCharacter* FindBestTarget(const float DotThreshold = 0.7f, const float SearchRange = 2000.f);
};
