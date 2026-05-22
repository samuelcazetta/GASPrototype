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
		if (!IsValid(TargetCharacter) || !TargetCharacter->IsAlive()) continue;
		const AGASP_BaseCharacter* Avatar = Cast<AGASP_BaseCharacter>(MeshComp->GetOwner());
		if (!IsValid(Avatar)) continue;
		UAbilitySystemComponent* AbilitySystemComponent = Avatar->GetAbilitySystemComponent();
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
