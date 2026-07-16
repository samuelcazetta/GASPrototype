// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GASP_BasePickUp.generated.h"

class USphereComponent;
class UGameplayEffect;
class UParticleSystemComponent;

UCLASS()
class GASPROTOTYPE_API AGASP_BasePickUp : public AActor
{
	GENERATED_BODY()

public:
	AGASP_BasePickUp();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASP|PickUp")
	TSubclassOf<UGameplayEffect> PickUpEffect;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GASP|PickUp")
	TObjectPtr<USphereComponent> SphereCollision;
	
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly, Category = "GASP|PickUp")
	TObjectPtr<UParticleSystemComponent> PickUpParticleComponent;
public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
