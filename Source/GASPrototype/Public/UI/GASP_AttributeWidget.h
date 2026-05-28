// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GASP_AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "GASP_AttributeWidget.generated.h"

class UGASP_AttributeSet;
/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API UGASP_AttributeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP|Attribute")
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASP|Attribute")
	FGameplayAttribute MaxAttribute;


	void OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair,
	                        const UGASP_AttributeSet* AttributeSet,
	                        float OldValue);
	
	bool MatchesAttribute(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;
	
	//Callable from BP only
	UFUNCTION(BlueprintImplementableEvent, meta =(DisplayName = "OnAttributeChanged"), Category = "GASP|Widget")
	void BP_OnAttributechanged(float NewValue, float NewMaxValue, float OldValue);

	UPROPERTY(BlueprintReadOnly, Category = "GASP|Widget")
	TWeakObjectPtr<AActor> AvatarActor;
};
