// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GASP_AttributeWidget.h"
#include "Components/WidgetComponent.h"
#include "GASP_WidgetComponent.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;
class UGASP_AttributeSet;
class UGASP_AbilitySystemComponent;
class AGASP_BaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GASPROTOTYPE_API UGASP_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UGASP_WidgetComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, Category = "GASP|Attribute")
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;

private:
	TWeakObjectPtr<AGASP_BaseCharacter> BaseCharacter;
	TWeakObjectPtr<UGASP_AbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UGASP_AttributeSet> AttributeSet;
	TArray<TPair<FGameplayAttribute, FDelegateHandle>> AttributeChangeDelegateHandles;
	bool bAttributeDelegatesBound = false;

	void InitializeAbilitySystemData();
	bool IsASCInitialized() const;
	void InitializeAttributeDelegate();
	void BindWidgetsToAttributeChanges(UWidget* WidgetObject,
	                                   const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair);
	void ClearAttributeChangeDelegates();

	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AttributeSet);
	UFUNCTION()
	void BindToAttributeChanges();
};
