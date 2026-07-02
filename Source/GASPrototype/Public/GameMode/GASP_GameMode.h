// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GASP_GameMode.generated.h"

class AGASP_BaseCharacter;

/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API AGASP_GameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	int32 CurrentPawnIndex = INDEX_NONE;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASP|GameMode")
	TArray<TSubclassOf<AGASP_BaseCharacter>> Pawns;
public:
	
	
	UFUNCTION(BlueprintPure, Category = "GASP|GameMode")
	FVector GetRandomSpawnPoint();
	
	UFUNCTION(BlueprintCallable, Category = "GASP|GameMode")
	void SwitchCharacter(APlayerController* PlayerController);
};
