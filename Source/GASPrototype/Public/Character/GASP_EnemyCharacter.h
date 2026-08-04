// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASP_BaseCharacter.h"
#include "GASP_EnemyCharacter.generated.h"

class UGASP_AbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyRespawn);

UCLASS()
class GASPROTOTYPE_API AGASP_EnemyCharacter : public AGASP_BaseCharacter
{
	GENERATED_BODY()

public:
	AGASP_EnemyCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;

	float GetLookAtRange() const { return LookAtRange; }
	FVector GetStartLocation() const { return StartLocation; }
	void SetStartLocation(const FVector& NewStartPosition);

	//Delegate for Item Drop outside GAS
	UPROPERTY(BlueprintAssignable)
	FOnEnemyDied OnDied;
	UPROPERTY(BlueprintAssignable)
	FOnEnemyDied OnRespawn;
	
	virtual void ResetAttributes() override;
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GASP|AI|Setup")
	FVector StartLocation{ 0, 0, 0 };
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="GASP|AI|Setup")
	FVector LimboLocation{ 0, 0, 0 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GASP|AI|Setup")
	float LookAtRange{ 1200.f };
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GASP|AI|Setup")
	float RespawnDelay{ 20.f };
	
	virtual void HandleDeath() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UGASP_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
};
