// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASP_BlueprintFunctionLibrary.generated.h"

struct FGameplayEventData;
struct FGameplayTag;
class USkeletalMeshComponent;

UCLASS()
class GASPROTOTYPE_API UGASP_BlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void SendEventsToActor(TArray<FHitResult> HitResults, const USkeletalMeshComponent* MeshComp,
	                              const FGameplayTag& EventTag);
};
