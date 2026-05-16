// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GASP_BaseCharacter.generated.h"

UCLASS()
class GASPROTOTYPE_API AGASP_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASP_BaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
};
