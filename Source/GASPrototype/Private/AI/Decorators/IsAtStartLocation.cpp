// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/IsAtStartLocation.h"

#include "AIController.h"
#include "Character/GASP_EnemyCharacter.h"

UIsAtStartLocation::UIsAtStartLocation()
{
	NodeName = TEXT("Is At Start Location");
}

bool UIsAtStartLocation::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	const AGASP_EnemyCharacter* AICharacter =	AIController ? Cast<AGASP_EnemyCharacter>(AIController->GetPawn()) : nullptr;

	if (!IsValid(AICharacter))
	{
		return false;
	}

	const float DistanceSq = FVector::DistSquared(AICharacter->GetActorLocation(),AICharacter->GetStartLocation());

	return DistanceSq > FMath::Square(50.f);
}
