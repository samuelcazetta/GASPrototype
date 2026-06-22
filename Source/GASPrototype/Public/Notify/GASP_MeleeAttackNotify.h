// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GASP_MeleeAttackNotify.generated.h"


UCLASS()
class GASPROTOTYPE_API UGASP_MeleeAttackNotify : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bEnableDebug = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName SocketName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ExtendedSocketDistance {90.f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CapsuleRadius {25.f};
	
	TArray<FHitResult> PerformSphereTrace(const USkeletalMeshComponent* MeshComp) const;  
};
