// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASP_GameplayAbility.h"
#include "GASP_HitReact.generated.h"

/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API UGASP_HitReact : public UGASP_GameplayAbility
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "GAS|Abilities")
	void CacheHitDirectionVectors(AActor* Instigator);
	
	UPROPERTY(BlueprintReadOnly, Category = "GAS|Abilities")
	FVector AvatarForward;
	
	UPROPERTY(BlueprintReadOnly, Category = "GAS|Abilities")
	FVector ToInstigator;
};
