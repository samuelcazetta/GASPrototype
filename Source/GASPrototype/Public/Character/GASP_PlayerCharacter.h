// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASP_BaseCharacter.h"
#include "GASP_PlayerCharacter.generated.h"

class UPostProcessComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GASPROTOTYPE_API AGASP_PlayerCharacter : public AGASP_BaseCharacter
{
	GENERATED_BODY()

public:
	AGASP_PlayerCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	UFUNCTION(BlueprintCallable)
	UPostProcessComponent* GetPostProcessComponent() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpecialAttackFade(bool bIsFadeIn);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UPostProcessComponent> PostProcessComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
