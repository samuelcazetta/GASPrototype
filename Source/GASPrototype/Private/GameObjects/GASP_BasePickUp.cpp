// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObjects/GASP_BasePickUp.h"

#include "AbilitySystemComponent.h"
#include "Character/GASP_PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"


AGASP_BasePickUp::AGASP_BasePickUp()
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);
	
	PickUpParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PickUp Particle"));
	RootComponent = PickUpParticleComponent;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereCollision->SetupAttachment(PickUpParticleComponent);
	
}

void AGASP_BasePickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!HasAuthority()) return;

	const AGASP_PlayerCharacter* PlayerCharacter = Cast<AGASP_PlayerCharacter>(OtherActor);
	if (!IsValid(PlayerCharacter)) return;

	UAbilitySystemComponent* ASC = PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(ASC)) return;

	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(PickUpEffect, 1.f, ContextHandle);
	ContextHandle.AddSourceObject(this);
	if (!SpecHandle.IsValid()) return;

	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	Destroy();
}

