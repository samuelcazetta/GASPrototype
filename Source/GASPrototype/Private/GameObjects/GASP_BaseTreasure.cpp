// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObjects/GASP_BaseTreasure.h"
#include "Character/GASP_EnemyCharacter.h"
#include "Components/ChildActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameObjects/GASP_BasePickUp.h"
#include "Net/UnrealNetwork.h"


AGASP_BaseTreasure::AGASP_BaseTreasure()
{
	PrimaryActorTick.bCanEverTick = false;

	SetReplicates(true);

	Chest = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Chest"));
	SetRootComponent(Chest);

	PickUp = CreateDefaultSubobject<UChildActorComponent>(TEXT("Pickup"));
	PickUp->SetupAttachment(Chest);
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
}

void AGASP_BaseTreasure::OnRep_Unlocked()
{
	if (!bUnlocked) return;
	ApplyUnlockedState();
}

void AGASP_BaseTreasure::ApplyUnlockedState()
{
	AGASP_BasePickUp* PickUpActor = Cast<AGASP_BasePickUp>(PickUp->GetChildActor());
	if (!IsValid(PickUpActor)) return;

	PickUpActor->SetActorHiddenInGame(false);
	PickUpActor->SetActorEnableCollision(true);
	
	OnTreasureUnlocked();
}

void AGASP_BaseTreasure::Init()
{
	AGASP_BasePickUp* PickUpActor = Cast<AGASP_BasePickUp>(PickUp->GetChildActor());
	if (IsValid(PickUpActor))
	{
		if (bUnlocked)
		{
			ApplyUnlockedState();
		}
		else
		{
			PickUpActor->SetActorHiddenInGame(true);
			PickUpActor->SetActorEnableCollision(false);
		}
	}

	if (!IsValid(Guard)) return;
	Guard->OnDied.AddDynamic(this, &AGASP_BaseTreasure::UnlockTreasure);
}

void AGASP_BaseTreasure::BeginPlay()
{
	Super::BeginPlay();
	Init();
}
