// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GASP_HitReact.h"

void UGASP_HitReact::CacheHitDirectionVectors(AActor* Instigator)
{
	const AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!IsValid(AvatarActor) || !IsValid(Instigator))
	{
		AvatarForward = FVector::ForwardVector;
		ToInstigator = FVector::ForwardVector;
		return;
	}

	AvatarForward = AvatarActor->GetActorForwardVector().GetSafeNormal2D();
	
	const FVector AvatarLocation = AvatarActor->GetActorLocation();
	const FVector InstigatorLocation = Instigator->GetActorLocation();
	
	ToInstigator = (InstigatorLocation - AvatarLocation).GetSafeNormal2D();
	if (ToInstigator.IsNearlyZero())
	{
		ToInstigator = AvatarForward;
	}
}
