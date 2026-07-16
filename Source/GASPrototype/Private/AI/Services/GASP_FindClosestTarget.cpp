// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/GASP_FindClosestTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/GASP_EnemyCharacter.h"
#include "Character/GASP_PlayerCharacter.h"
#include "Utility/GASP_BlueprintFunctionLibrary.h"

UGASP_FindClosestTarget::UGASP_FindClosestTarget()
{
	NodeName = TEXT("Find Closest Target");
}

void UGASP_FindClosestTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	

	// Checks
	AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner());
	AGASP_EnemyCharacter* AICharacter = AIController ? Cast<AGASP_EnemyCharacter>(AIController->GetPawn()) : nullptr;
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(AIController) || !IsValid(AICharacter) || !IsValid(Blackboard)) return;
	
	// Find nearest Target
	AGASP_PlayerCharacter* ClosestTarget = nullptr;
	float ClosestDistanceSq = TNumericLimits<float>::Max();
	const FVector StartLocation = AICharacter->GetStartLocation();
	for (const FHitResult& Hit : UGASP_BlueprintFunctionLibrary::FindCharactersInRange(
		     AICharacter, StartLocation, AICharacter->GetLookAtRange(), true))
	{
		AGASP_PlayerCharacter* Player = Cast<AGASP_PlayerCharacter>(Hit.GetActor());
		if (!IsValid(Player) || !Player->IsAlive()) continue;

		const float DistanceSq = FVector::DistSquared(StartLocation, Player->GetActorLocation());
		if (DistanceSq < ClosestDistanceSq)
		{
			ClosestDistanceSq = DistanceSq;
			ClosestTarget = Player;
		}
	}

	if (!IsValid(ClosestTarget))
	{
		Blackboard->ClearValue(GetSelectedBlackboardKey());
		return;
	}
	
	Blackboard->SetValueAsObject(GetSelectedBlackboardKey(), ClosestTarget);
}
