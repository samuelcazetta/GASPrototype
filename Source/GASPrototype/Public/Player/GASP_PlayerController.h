// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GASP_PlayerController.generated.h"

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
private:
	
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
	
	void Jump();
	void StopJumping();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	bool IsAlive() const;
	
};
