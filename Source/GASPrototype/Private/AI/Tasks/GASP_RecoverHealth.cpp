// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/GASP_RecoverHealth.h"

#include "AIController.h"
#include "Character/GASP_EnemyCharacter.h"
#include "GameplayTags/GASP_AbilityTags.h"

UGASP_RecoverHealth::UGASP_RecoverHealth()
{
	NodeName = TEXT("Recover Health");
}

EBTNodeResult::Type UGASP_RecoverHealth::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
		
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController)) return EBTNodeResult::Failed;
	
	AGASP_EnemyCharacter* AICharacter = Cast<AGASP_EnemyCharacter>(AIController->GetPawn());
	if (!IsValid(AICharacter) || !AICharacter->IsAlive()) return EBTNodeResult::Failed;
	
	AICharacter->ActivateAbility(GASPTags::Abilities::Enemy::HealthRecover);
	
	return EBTNodeResult::Succeeded;
}
