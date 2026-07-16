// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/GASP_ClearBlackboardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UGASP_ClearBlackboardValue::UGASP_ClearBlackboardValue()
{
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UGASP_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent(); IsValid(Blackboard)) Blackboard->
		ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}
