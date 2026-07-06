// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASP_BlueprintFunctionLibrary.generated.h"

class AGASP_BaseCharacter;
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
	
	UFUNCTION(BlueprintCallable, Category = "GASP|Utility")
	static bool IsFacingDirection(const FVector& Forward, const FVector& TargetDirection, float Threshold = -0.5f);

	UFUNCTION(BlueprintPure, Category = "GASP|Utility")
	static EHitDirection GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator);
	
	UFUNCTION(BlueprintPure, Category = "GASP|Utility")
	static FName GetHitDirectionName(const EHitDirection& EHitDirection);
	
	UFUNCTION(BlueprintCallable, Category = "GASP|Utility")
	static TArray<FHitResult> FindCharactersInRange(AActor* Instigator, const FVector& Origin, float Radius = 100.f,
	                                                bool bDrawDebug = false);
	
	UFUNCTION(BlueprintCallable, Category = "GASP|Utility", meta = (WorldContext = "WorldContextObject"))
	static TArray<AActor*> ApplyKnockback(UObject* WorldContextObject, AActor* AvatarActor, const TArray<AActor*>& HitActors,
													 float InnerRadius,
													 float OuterRadius, float LaunchForceMagnitude, float RotationAngle,
													 bool bDrawnDebug);
	
	
	//todo: rotate towards target
};
