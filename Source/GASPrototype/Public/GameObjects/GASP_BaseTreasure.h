// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GASP_BaseTreasure.generated.h"

class AGASP_BasePickUp;
class AGASP_EnemyCharacter;
class UChildActorComponent;
class USkeletalMeshComponent;

UCLASS()
class GASPROTOTYPE_API AGASP_BaseTreasure : public AActor
{
	GENERATED_BODY()

public:
	AGASP_BaseTreasure();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "GASP|Treasure")
	TObjectPtr<AGASP_EnemyCharacter> Guard;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GASP|Treasure")
	TObjectPtr<USkeletalMeshComponent> Chest;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASP|Treasure")
	TSubclassOf<AGASP_BasePickUp> PickUp;
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayOpenAnimation();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayCloseAnimation();
	
	virtual void BeginPlay() override;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Unlocked)
	bool bUnlocked {false};

	UFUNCTION()
	void OnRep_Unlocked();
	
	UFUNCTION()
	void UnlockTreasure();
	UFUNCTION()
	void ReLockTreasure();

	void Init();
	void ApplyUnlockedState();
};
