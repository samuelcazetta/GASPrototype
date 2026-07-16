// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "GASP_IsAlive.generated.h"

/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API UGASP_IsAlive : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UGASP_IsAlive();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
