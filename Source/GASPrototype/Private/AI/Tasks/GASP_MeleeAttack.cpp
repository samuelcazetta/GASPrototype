// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/GASP_MeleeAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/GASP_EnemyCharacter.h"
#include "Character/GASP_PlayerCharacter.h"
#include "GameplayTags/GASP_AbilityTags.h"

UGASP_MeleeAttack::UGASP_MeleeAttack()
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UGASP_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController)) return EBTNodeResult::Failed;
	
	AGASP_EnemyCharacter* AICharacter = Cast<AGASP_EnemyCharacter>(AIController->GetPawn());
	if (!IsValid(AICharacter) || !AICharacter->IsAlive()) return EBTNodeResult::Failed;
	
	AICharacter->ActivateAbility(GASPTags::Abilities::Enemy::Attack);
	
	return EBTNodeResult::Succeeded;
}
