// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GASP_BaseProjectile.generated.h"

class UGameplayEffect;
class UProjectileMovementComponent;

UCLASS()
class GASPROTOTYPE_API AGASP_BaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	AGASP_BaseProjectile();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASP|Projectile")
	float LifeSpan{10.0f};
	

private:
	UPROPERTY(VisibleAnywhere, Category = "GASP|Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMoveComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "GASP|Projectile")
	TSubclassOf<UGameplayEffect> DamageEffect;
};
