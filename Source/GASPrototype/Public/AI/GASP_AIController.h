// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "GASP_AIController.generated.h"

class AGASP_PlayerCharacter;

UCLASS()
class GASPROTOTYPE_API AGASP_AIController : public AAIController
{
	GENERATED_BODY()

public:
	AGASP_AIController();
private:
	void StartBehaviorTree();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASP|AI")
	TObjectPtr<AGASP_PlayerCharacter> CurrentTarget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASP|AI")
	TObjectPtr<UBehaviorTree> EnemyAI;
	
	virtual void BeginPlay() override;
	
	
	/*
	todo:
	void Jump();
	void Attack();
	void Dash();
	void Special(); 
	bool IsAlive() const;
	*/
};
