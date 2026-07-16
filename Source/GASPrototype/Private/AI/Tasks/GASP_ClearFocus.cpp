// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/GASP_ClearFocus.h"

#include "AIController.h"

UGASP_ClearFocus::UGASP_ClearFocus()
{
	NodeName = TEXT("Clear Focus");
}

EBTNodeResult::Type UGASP_ClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AAIController* Controller = Cast<AAIController>(OwnerComp.GetOwner());
	if (!IsValid(Controller)) return EBTNodeResult::Failed;
	
	Controller->ClearFocus(EAIFocusPriority::Gameplay);
	
	return EBTNodeResult::Succeeded;
}
