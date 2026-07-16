// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/GASP_UpdateFocus.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UGASP_UpdateFocus::UGASP_UpdateFocus()
{
	NodeName = TEXT("Update Focus");
}

void UGASP_UpdateFocus::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	// Checks
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(AIController) || !IsValid(Blackboard))	return;

	// Current target
	AActor* CurrentTarget = Cast<AActor>(Blackboard->GetValueAsObject(GetSelectedBlackboardKey()));

	if (IsValid(CurrentTarget))
	{
		AIController->SetFocus(CurrentTarget);
	}
	else
	{
		AIController->ClearFocus(EAIFocusPriority::Gameplay);
	}
}
