// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASP_BlueprintFunctionLibrary.generated.h"

struct FGameplayEventData;
struct FGameplayTag;
class USkeletalMeshComponent;

UENUM(BlueprintType)
enum class EHitDirection: uint8
{
	Left,
	Right,
	Front,
	Back,
};

UCLASS()
class GASPROTOTYPE_API UGASP_BlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void SendEventsToActor(TArray<FHitResult> HitResults, const USkeletalMeshComponent* MeshComp,
	                              const FGameplayTag& EventTag);
	
	UFUNCTION(BlueprintPure, Category = "GASP|Utility")
	static EHitDirection GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator);
	
	UFUNCTION(BlueprintPure, Category = "GASP|Utility")
	static FName GetHitDirectionName(const EHitDirection& EHitDirection);
	
	//todo: rotate towards target
};
