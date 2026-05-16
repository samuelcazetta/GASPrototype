// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPrototype/Public/Character/GASP_BaseCharacter.h"


// Sets default values
AGASP_BaseCharacter::AGASP_BaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AGASP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}