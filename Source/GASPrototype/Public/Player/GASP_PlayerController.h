// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GASP_PlayerController.generated.h"

class AGASP_BaseCharacter;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class GASPROTOTYPE_API AGASP_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UPROPERTY()
	TObjectPtr<AGASP_BaseCharacter> BaseCharacter;

	// List of IMC
	UPROPERTY(EditDefaultsOnly, Category="GASP|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;

	//Move and Look
	UPROPERTY(EditDefaultsOnly, Category="GASP|Input|Movement")
	TObjectPtr<UInputAction> JumpInputAction;
	UPROPERTY(EditDefaultsOnly, Category="GASP|Input|Movement")
	TObjectPtr<UInputAction> MoveInputAction;
	UPROPERTY(EditDefaultsOnly, Category="GASP|Input|Movement")
	TObjectPtr<UInputAction> LookInputAction;

	//Skills
	UPROPERTY(EditDefaultsOnly, Category="GASP|Input|Skills")
	TObjectPtr<UInputAction> AttackInputAction;
	UPROPERTY(EditDefaultsOnly, Category="GASP|Input|Skills")
	TObjectPtr<UInputAction> DashInputAction;
	UPROPERTY(EditDefaultsOnly, Category="GASP|Input|Skills")
	TObjectPtr<UInputAction> SpecialInputAction;

	void Jump();
	void StopJumping();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void Attack();
	void Dash();
	void Special();

	bool IsAlive() const;
};
