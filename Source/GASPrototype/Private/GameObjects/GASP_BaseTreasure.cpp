// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObjects/GASP_BaseTreasure.h"
#include "Character/GASP_EnemyCharacter.h"
#include "Components/ChildActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameObjects/GASP_BasePickUp.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


AGASP_BaseTreasure::AGASP_BaseTreasure()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Chest = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Chest"));
	SetRootComponent(Chest);
}

void AGASP_BaseTreasure::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGASP_BaseTreasure, bUnlocked);
}

void AGASP_BaseTreasure::UnlockTreasure()
{
	if (!HasAuthority() || bUnlocked) return;

	bUnlocked = true;
	ApplyUnlockedState();
	PlayOpenAnimation(); // animation on server
}

void AGASP_BaseTreasure::ReLockTreasure()
{
	if (!HasAuthority() || !bUnlocked) return;

	bUnlocked = false;
	PlayCloseAnimation(); // animation on server
}

void AGASP_BaseTreasure::OnRep_Unlocked()
{
	// animations on clients
	
	if (bUnlocked)
	{
		PlayOpenAnimation();
	}
	else
	{
		PlayCloseAnimation();
	}
}

void AGASP_BaseTreasure::ApplyUnlockedState()
{
	if (!HasAuthority()) return;
	if (!IsValid(PickUp)) return;

	FVector SpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
	GetWorld()->SpawnActor<AGASP_BasePickUp>(PickUp, SpawnLocation, FRotator::ZeroRotator);
}

void AGASP_BaseTreasure::Init()
{
	if (IsValid(PickUp))
	{
		if (bUnlocked)
		{
			ApplyUnlockedState();
		}
	}

	if (!IsValid(Guard)) return;
	Guard->OnDied.AddDynamic(this, &AGASP_BaseTreasure::UnlockTreasure);
	Guard->OnRespawn.AddDynamic(this, &AGASP_BaseTreasure::ReLockTreasure);
}

void AGASP_BaseTreasure::BeginPlay()
{
	Super::BeginPlay();
	Init();
}
