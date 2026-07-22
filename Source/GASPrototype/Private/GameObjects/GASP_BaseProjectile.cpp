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
	if (!IsValid(AbilitySystemComponent)) return;
	//if (!IsValid(AbilitySystemComponent) || !HasAuthority()) return;
	
	// Apply Damage GE
	FGameplayEffectContextHandle DamageContextHandle = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle DamageEffectSpec = AbilitySystemComponent->MakeOutgoingSpec(DamageEffect, 1.f, DamageContextHandle);
	if (!DamageEffectSpec.IsValid()) return;
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*DamageEffectSpec.Data.Get());
	
	// Hit React Event
	FHitResult HitResult;
	HitResult.ImpactPoint = GetActorLocation();
	DamageContextHandle.AddHitResult(HitResult);
	FGameplayEventData Payload;
	Payload.Instigator = GetInstigator();
	Payload.ContextHandle = DamageContextHandle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(BaseCharacter, GASPTags::Events::HitReact, Payload);
	
	// Apply Power Charge GE
	if (IsValid(OnHitPowerChargeEffect))
	{
		const AGASP_PlayerCharacter* OwnerCharacter = Cast<AGASP_PlayerCharacter>(GetOwner());
		if (!IsValid(OwnerCharacter)) return;
		UAbilitySystemComponent* OwnerASC = OwnerCharacter->GetAbilitySystemComponent();
		if (!IsValid(OwnerASC)) return;
		
		FGameplayEffectContextHandle PowerChargeContextHandle = OwnerASC->MakeEffectContext();
		FGameplayEffectSpecHandle PowerChargeEffectSpec = OwnerASC->MakeOutgoingSpec(OnHitPowerChargeEffect, 1.f, PowerChargeContextHandle);
		if (!PowerChargeEffectSpec.IsValid()) return;
		OwnerASC->ApplyGameplayEffectSpecToSelf(*PowerChargeEffectSpec.Data.Get());
	}
	
	Destroy();
}

void AGASP_BaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
}

