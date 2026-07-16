// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "IsAtStartLocation.generated.h"

/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API UIsAtStartLocation : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
	UIsAtStartLocation();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
};
