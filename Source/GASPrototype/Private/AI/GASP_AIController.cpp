// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GASP_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/GASP_EnemyCharacter.h"
#include "GameFramework/Character.h"


AGASP_AIController::AGASP_AIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGASP_AIController::StartBehaviorTree()
{
	if (!IsValid(EnemyAI)) return;
	RunBehaviorTree(EnemyAI);

	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (!IsValid(BlackboardComponent)) return;

	BlackboardComponent->SetValueAsVector("StartLocation", GetCharacter()->GetActorLocation());
}

void AGASP_AIController::BeginPlay()
{
	Super::BeginPlay();
	
	StartBehaviorTree();
	
	AGASP_EnemyCharacter* AICharacter = Cast<AGASP_EnemyCharacter>(GetCharacter());
	if (!IsValid(AICharacter)) return;
	AICharacter->SetStartLocation(GetCharacter()->GetActorLocation());
}
