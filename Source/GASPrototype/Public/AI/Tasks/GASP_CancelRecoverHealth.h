// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GASP_CancelRecoverHealth.generated.h"

/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API UGASP_CancelRecoverHealth : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UGASP_CancelRecoverHealth();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
