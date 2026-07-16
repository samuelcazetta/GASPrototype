// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/GASP_IsAlive.h"

#include "AIController.h"
#include "AssetTypeCategories.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/GASP_EnemyCharacter.h"

UGASP_IsAlive::UGASP_IsAlive()
{
	NodeName = TEXT("Is Alive");
}

void UGASP_IsAlive::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner());
	AGASP_EnemyCharacter* AICharacter = AIController ? Cast<AGASP_EnemyCharacter>(AIController->GetPawn()) : nullptr;
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(AIController) || !IsValid(AICharacter) || !IsValid(Blackboard)) return;

	if (!AICharacter->IsAlive())
	{
		AIController->StopMovement();
		AIController->ClearFocus(EAssetTypeCategories::Gameplay);
	}
	
	Blackboard->SetValueAsBool(GetSelectedBlackboardKey(), AICharacter->IsAlive());
}

