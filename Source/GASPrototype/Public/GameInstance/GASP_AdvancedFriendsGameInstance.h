// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "GameplayTagContainer.h"
#include "GASP_AdvancedFriendsGameInstance.generated.h"
 
/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API UGASP_AdvancedFriendsGameInstance : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "GASP|GameInstance")
	FGameplayTag SelectedCharacterTag;
};
