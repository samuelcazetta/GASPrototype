// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASP_BaseCharacter.h"
#include "GASP_EnemyCharacter.generated.h"

class UGASP_AbilitySystemComponent;

UCLASS()
class GASPROTOTYPE_API AGASP_EnemyCharacter : public AGASP_BaseCharacter
{
	GENERATED_BODY()

public:
	AGASP_EnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
	float GetLookAtRange() const {return LookAtRange;}
	FVector GetStartLocation() const {return StartLocation;}
	void SetStartLocation(const FVector& NewStartPosition);
	

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GASP|AI|Setup")
	FVector StartLocation{ 0, 0, 0 };
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GASP|AI|Setup")
	float LookAtRange{1200.f};
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UGASP_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
};
