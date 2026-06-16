// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GASP_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API AGASP_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	FVector GetRandomSpawnPoint();
};
