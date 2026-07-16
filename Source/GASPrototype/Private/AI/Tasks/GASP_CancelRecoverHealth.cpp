// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/GASP_CancelRecoverHealth.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "Character/GASP_EnemyCharacter.h"
#include "GameplayTags/GASP_EffectTags.h"

UGASP_CancelRecoverHealth::UGASP_CancelRecoverHealth()
{
	NodeName = TEXT("Cancel Recover Health");
}

EBTNodeResult::Type UGASP_CancelRecoverHealth::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	const AAIController* AIController = OwnerComp.GetAIOwner();
	const AGASP_EnemyCharacter* AICharacter = AIController
		                                          ? Cast<AGASP_EnemyCharacter>(AIController->GetPawn())
		                                          : nullptr;

	if (!IsValid(AICharacter)) return EBTNodeResult::Failed;

	FGameplayTagContainer Tags;
	Tags.AddTag(GASPTags::Effects::Healing::Regen);

	UAbilitySystemComponent* ASC = AICharacter->GetAbilitySystemComponent();
	if (! IsValid(ASC)) return EBTNodeResult::Failed;
	
	ASC->RemoveActiveEffectsWithTags(Tags);
	
	return EBTNodeResult::Succeeded;
}
