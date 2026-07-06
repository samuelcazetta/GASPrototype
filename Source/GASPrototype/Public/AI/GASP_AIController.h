// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "GASP_AIController.generated.h"

UCLASS()
class GASPROTOTYPE_API AGASP_AIController : public AAIController
{
	GENERATED_BODY()

public:
	AGASP_AIController();

protected:
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
