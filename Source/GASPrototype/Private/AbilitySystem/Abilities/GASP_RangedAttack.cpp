// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GASP_RangedAttack.h"

#include "Character/GASP_BaseCharacter.h"
#include "Utility/GASP_BlueprintFunctionLibrary.h"


AGASP_BaseCharacter* UGASP_RangedAttack::FindBestTarget(const float DotThreshold, const float SearchRange)
{
	AActor* Owner = GetAvatarActorFromActorInfo();
	if (!IsValid(Owner)) return nullptr;

	TArray<AGASP_BaseCharacter*> Candidates = UGASP_BlueprintFunctionLibrary::FindCharactersInRange(
		Owner, SearchRange);
	if (Candidates.IsEmpty()) return nullptr;

	const FVector OwnerLocation = Owner->GetActorLocation();
	const FVector Forward = Owner->GetActorForwardVector().GetSafeNormal2D();

	float BestDot = DotThreshold;  //  0.7f would be something like 45°
	AGASP_BaseCharacter* BestTarget = nullptr;

	for (AGASP_BaseCharacter* Candidate : Candidates)
	{
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
