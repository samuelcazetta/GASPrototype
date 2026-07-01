// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/GASP_BlueprintFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Character/GASP_BaseCharacter.h"
#include "Engine/OverlapResult.h"

void UGASP_BlueprintFunctionLibrary::SendEventsToActor(TArray<FHitResult> HitResults,
                                                       const USkeletalMeshComponent* MeshComp,
                                                       const FGameplayTag& EventTag)
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

TArray<AGASP_BaseCharacter*> UGASP_BlueprintFunctionLibrary::FindCharactersInRange(AActor* Origin, const float Radius)
{
	if (Origin == nullptr) return {};
	const UWorld* World = Origin->GetWorld();
	if (World == nullptr) return {};
	
	TArray<FOverlapResult> OutOverlaps;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Origin);
	World->OverlapMultiByObjectType(OutOverlaps, Origin->GetActorLocation(), FQuat::Identity, FCollisionObjectQueryParams(ECC_Pawn),
	                                FCollisionShape::MakeSphere(Radius),Params);

	TArray<AGASP_BaseCharacter*> Characters;
	for (const FOverlapResult& Overlap : OutOverlaps)
	{
		AGASP_BaseCharacter* Character = Cast<AGASP_BaseCharacter>(Overlap.GetActor());
		if (!IsValid(Character))continue;
		Characters.AddUnique(Character);
	}

	return Characters;
}

TArray<AActor*> UGASP_BlueprintFunctionLibrary::ApplyKnockback(UObject* WorldContextObject, AActor* AvatarActor, const TArray<AActor*>& HitActors,
	float InnerRadius, float OuterRadius, float LaunchForceMagnitude, float RotationAngle, bool bDrawnDebug)
{
	for (auto HitActor : HitActors)
	{
		ACharacter* HitCharacter = Cast<ACharacter>(HitActor);
		if (!IsValid(HitCharacter) || !IsValid(AvatarActor)) return TArray<AActor*>();

		// Get each one position
		const FVector HitCharacterLocation = HitCharacter->GetActorLocation();
		const FVector AvatarLocation = AvatarActor->GetActorLocation();

		// Calculates the direction of who push towards whom get pushed (nock direction)
		const FVector ToHitActor = HitCharacterLocation - AvatarLocation;

		// dist between the two
		const float Distance = FVector::Dist(AvatarLocation, HitCharacterLocation);

		float LaunchForce = 0.f;
		if (Distance > OuterRadius) continue; // If character is too far, doesn't launch
		if (Distance <= InnerRadius)
		{
			// max push
			LaunchForce = LaunchForceMagnitude;
		}
		else
		{
			// less push in between
			const FVector2D FalloffRange(InnerRadius, OuterRadius);
			const FVector2D LaunchForceRanged(LaunchForceMagnitude, 0.f);
			LaunchForce = FMath::GetMappedRangeValueClamped(FalloffRange, LaunchForceRanged, Distance);
		}

		if (bDrawnDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
			                                 FString::Printf(TEXT("LaunchForce: %f"), LaunchForce));
		}

		// push direction
		FVector KnockbackForce = ToHitActor.GetSafeNormal();
		// ignores z
		KnockbackForce.Z = 0.f;

		// Calculate the "to the right" vector of the push (90 degrees on the ground), like rotating a ruler.
		const FVector Right = KnockbackForce.RotateAngleAxis(90.f, FVector::UpVector);

		// Rotates the push by RotationAngle around the right axis: this tilts the vector
		// upwards, causing the character to fly in an arc instead of just sliding along the ground.
		KnockbackForce = KnockbackForce.RotateAngleAxis(-RotationAngle, Right) * LaunchForce;

		if (bDrawnDebug)
		{
			DrawDebugDirectionalArrow(AvatarActor->GetWorld(), HitCharacterLocation,
			                          HitCharacterLocation + KnockbackForce, 100.f, FColor::Red, false, 1.f, 0, 1.f);
		}

		//todo: Prevents the EnemyCharacter from continuing to move until it lands
		/*
		if (AGAS_EnemyCharacter* EnemyCharacter = Cast<AGAS_EnemyCharacter>(HitCharacter); IsValid(EnemyCharacter))
		{
			EnemyCharacter->StopMovementUntilLanded();
		}
		*/
		
		// Launch
		HitCharacter->LaunchCharacter(KnockbackForce, true, true);
	}

	// returns launched actors
	return HitActors;
}


bool UGASP_BlueprintFunctionLibrary::IsFacingDirection(const FVector& Forward,
                                                       const FVector& TargetDirection, const float Threshold)
{
	// Threshold -0.5 = 120º angle

	const float Dot = FVector::DotProduct(
		Forward.GetSafeNormal2D(),
		TargetDirection.GetSafeNormal2D());

	return Dot >= Threshold;
}
