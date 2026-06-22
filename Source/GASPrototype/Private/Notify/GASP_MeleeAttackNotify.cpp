// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/GASP_MeleeAttackNotify.h"
#include "GameplayTags/GASP_EventTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utility/GASP_BlueprintFunctionLibrary.h"

void UGASP_MeleeAttackNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner())) return;

	// capsule trace
	const TArray<FHitResult> HitResults = PerformSphereTrace(MeshComp);
	
	
	// send caught actors to avatar 
	UGASP_BlueprintFunctionLibrary::SendEventsToActor(HitResults, MeshComp,
	                                                  GASPTags::Events::Attack::MeleeTraceHit);
}

TArray<FHitResult> UGASP_MeleeAttackNotify::PerformSphereTrace(const USkeletalMeshComponent* MeshComp) const
{
	// arguments
	const FTransform SocketTransform = MeshComp->GetSocketTransform(SocketName, RTS_World);
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ExtendedSocketDirection = UKismetMathLibrary::GetForwardVector(
		SocketTransform.GetRotation().Rotator()) * ExtendedSocketDistance;
	const FVector TraceEnd = TraceStart - ExtendedSocketDirection;
	
	
	TArray<FHitResult> HitResults;
	
	// capsule trace
	EDrawDebugTrace::Type Debug = bEnableDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
	UKismetSystemLibrary::SphereTraceMulti(MeshComp, TraceStart, TraceEnd, CapsuleRadius,
	                                       UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1),
	                                       false, TArray<AActor*>(), Debug, HitResults, true,
	                                       FLinearColor::Red, FLinearColor::Green, 0.3f);
	

	// return Pawns caught by trace
	return HitResults;
}
