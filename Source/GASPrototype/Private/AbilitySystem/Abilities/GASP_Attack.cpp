// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GASP_Attack.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Character/GASP_BaseCharacter.h"
#include "GameplayTags/GASP_EventTags.h"
#include "Utility/GASP_BlueprintFunctionLibrary.h"

void UGASP_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo,
                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// used just for the HandleConfirmedHit
	if (HitActors.Num() > 0)
		HitActors.Empty();
}

AGASP_BaseCharacter* UGASP_Attack::FindBestTarget(const float DotThreshold, const float SearchRange)
{
	AActor* Owner = GetAvatarActorFromActorInfo();
	if (!IsValid(Owner)) return nullptr;
	FVector Location = Owner->GetActorLocation();

	TArray<FHitResult> HitResults = UGASP_BlueprintFunctionLibrary::FindCharactersInRange(
		Owner, Location, SearchRange);
	
	if (HitResults.IsEmpty()) return nullptr;

	const FVector OwnerLocation = Owner->GetActorLocation();
	const FVector Forward = Owner->GetActorForwardVector().GetSafeNormal2D();

	float BestDot = DotThreshold;  //  0.7f would be something like 45°
	AGASP_BaseCharacter* BestTarget = nullptr;

	for (auto Hit : HitResults)
	{
		AGASP_BaseCharacter* Candidate = Cast<AGASP_BaseCharacter>(Hit.GetActor());
		if (!IsValid(Candidate) || !Candidate->IsAlive()) continue;

		const FVector Direction = (Candidate->GetActorLocation() - OwnerLocation).GetSafeNormal2D();

		const float Dot = FVector::DotProduct(Forward, Direction);
		if (Dot > BestDot)
		{
			BestDot = Dot;
			BestTarget = Candidate;
		}
	}
	return BestTarget;
}

// sends Hit React event and applies damage GE to hit actors.
void UGASP_Attack::HandleConfirmedHit(const FGameplayEventData& Payload,
                                                   const TSubclassOf<UGameplayEffect> DamageEffect,
                                                   bool bOncePerTarget, TSubclassOf<UGameplayEffect> SourceOnHitEffect)
{
	// Source
	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(SourceASC)) return;
	const AActor* SourceAvatar = GetAvatarActorFromActorInfo();
	if (!IsValid(SourceAvatar)) return;

	// Target
	const AGASP_BaseCharacter* TargetCharacter = Cast<AGASP_BaseCharacter>(Payload.Target.Get());
	if (!IsValid(TargetCharacter) || !TargetCharacter->IsAlive() || !TargetCharacter->IsTangible()) return;
	UAbilitySystemComponent* TargetASC = TargetCharacter->GetAbilitySystemComponent();
	if (!IsValid(TargetASC)) return;

	// No damage duplication safety
	if (bOncePerTarget)
	{
		if (HitActors.Contains(TargetCharacter)) return;
		HitActors.Add(TargetCharacter);
	}

	// Damage the Target
	if (IsValid(DamageEffect))
	{
		FGameplayEffectContextHandle DamageContextHandle = SourceASC->MakeEffectContext();
		DamageContextHandle.AddSourceObject(this);

		if (const FHitResult* HitResult = Payload.ContextHandle.GetHitResult())
		{
			DamageContextHandle.AddHitResult(*HitResult);
		}

		const FGameplayEffectSpecHandle DamageSpecHandle = SourceASC->MakeOutgoingSpec(
			DamageEffect, 1, DamageContextHandle);
		if (DamageSpecHandle.IsValid())
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());
		}
	}

	// Sends the hit reaction event to the target ASC.
	// Target's reaction ability most likely needs to be server-initiated, the source ASC can't directly drive target's ASC   
	FGameplayEventData HitReactPayload = Payload;
	HitReactPayload.Instigator = SourceAvatar;
	HitReactPayload.Target = TargetCharacter;
	AActor* TargetActor = TargetASC->GetOwner();
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetActor, GASPTags::Events::HitReact,
	                                                         HitReactPayload);

	// Source reward Power Gain
	if (IsValid(SourceOnHitEffect))
	{
		FGameplayEffectContextHandle SourceEffectContextHandle = SourceASC->MakeEffectContext();
		SourceEffectContextHandle.AddSourceObject(this);

		if (const FHitResult* HitResult = Payload.ContextHandle.GetHitResult())
		{
			SourceEffectContextHandle.AddHitResult(*HitResult);
		}

		const FGameplayEffectSpecHandle SourceEffectSpecHandle = SourceASC->MakeOutgoingSpec(
			SourceOnHitEffect, 1, SourceEffectContextHandle);
		if (SourceEffectSpecHandle.IsValid())
		{
			SourceASC->ApplyGameplayEffectSpecToSelf(*SourceEffectSpecHandle.Data.Get());
		}
	}
}
