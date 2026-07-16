// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObjects/GASP_BaseProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Character/GASP_PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayTags/GASP_EventTags.h"


// Sets default values
AGASP_BaseProjectile::AGASP_BaseProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	ProjectileMoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComponent"));
	
	
}

void AGASP_BaseProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	// Destroy when hitting world/static actors
	if (!OtherActor->IsA<AGASP_BaseCharacter>())
	{
		Destroy();
		return;
	}
	
	// checks
	AGASP_BaseCharacter* BaseCharacter = Cast<AGASP_BaseCharacter>(OtherActor);
	if (!IsValid(BaseCharacter) || !BaseCharacter->IsAlive() || IsOwnedBy(BaseCharacter)) return;
	UAbilitySystemComponent* AbilitySystemComponent = BaseCharacter->GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent) || !HasAuthority()) return;
	
	// Apply Damage
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle EffectSpec = AbilitySystemComponent->MakeOutgoingSpec(DamageEffect, 1.f, ContextHandle);
	if (!EffectSpec.IsValid()) return;
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
	
	// Hit React Event
	FHitResult HitResult;
	HitResult.ImpactPoint = GetActorLocation();
	ContextHandle.AddHitResult(HitResult);
	FGameplayEventData Payload;
	Payload.Instigator = GetInstigator();
	Payload.ContextHandle = ContextHandle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(BaseCharacter, GASPTags::Events::HitReact, Payload);
	
	Destroy();
}

void AGASP_BaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
}

