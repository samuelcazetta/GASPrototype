// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/GASP_BlueprintFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Character/GASP_BaseCharacter.h"

void UGASP_BlueprintFunctionLibrary::SendEventsToActor(TArray<FHitResult> HitResults, const USkeletalMeshComponent* MeshComp, const FGameplayTag& EventTag)
{
	for (auto Hit : HitResults)
	{
		// checks 
		AGASP_BaseCharacter* TargetCharacter = Cast<AGASP_BaseCharacter>(Hit.GetActor());
		if (!IsValid(TargetCharacter) || !TargetCharacter->IsAlive() || !TargetCharacter->IsTangible()) continue;
		UAbilitySystemComponent* AbilitySystemComponent = TargetCharacter->GetAbilitySystemComponent();
		if (!IsValid(AbilitySystemComponent)) continue;
		
		// context handle with Hit Result
		FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		ContextHandle.AddHitResult(Hit);
		
		// payload
		FGameplayEventData Payload;
		Payload.Target = TargetCharacter;
		Payload.ContextHandle = ContextHandle;
		Payload.Instigator = MeshComp->GetOwner();
		
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, Payload);
		
	}
	
}

EHitDirection UGASP_BlueprintFunctionLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const FVector SafeTargetForward = TargetForward.GetSafeNormal2D();
	const FVector SafeToInstigator = ToInstigator.GetSafeNormal2D();
	if (SafeTargetForward.IsNearlyZero() || SafeToInstigator.IsNearlyZero())
	{
		return EHitDirection::Front;
	}

	// Dot product tells front/back: negative = opposite directions (behind), positive = same direction (front)
	const float Dot = FVector::DotProduct(SafeTargetForward, SafeToInstigator);

	if (Dot < -0.5f) return EHitDirection::Back;

	if (Dot < 0.5f)
	{
		// Dot can't distinguish left/right, so use Cross product: Z < 0 means left
		const FVector Cross = FVector::CrossProduct(SafeTargetForward, SafeToInstigator);
		return Cross.Z < 0.f ? EHitDirection::Left : EHitDirection::Right;
	}

	return EHitDirection::Front;
}

FName UGASP_BlueprintFunctionLibrary::GetHitDirectionName(const EHitDirection& EHitDirection)
{
	switch (EHitDirection)
	{
	case EHitDirection::Left: return FName("Left");
	case EHitDirection::Right: return FName("Right");
	case EHitDirection::Back: return FName("Back");
	case EHitDirection::Front: return FName("Front");
	default: return FName("None");
	}
}
