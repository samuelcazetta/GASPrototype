// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GASP_AttributeSet.generated.h"

// Macro from Macros
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttributesInitialized); //Delegate for telling UI that AS is initialized
UCLASS()
class GASPROTOTYPE_API UGASP_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	
	// ReplicatedUsing = OnRep_Health → function will be called on CLIENT when replicated value arrives from server
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Power)
	FGameplayAttributeData Power;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxPower)
	FGameplayAttributeData MaxPower;
	
	UPROPERTY(ReplicatedUsing = OnRep_AttributesInitialized)
	bool bAttributesInitialized = false;
	
	UPROPERTY(BlueprintAssignable)
	FAttributesInitialized OnAttributesInitialized;
	
	
	// Every replicated variable must register its replication here. Required when using UPROPERTY(Replicated).
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	// Inherited hook that runs logic after a GameplayEffect has been applied.
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_Power(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_MaxPower(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_AttributesInitialized();

	// Auto-generates GetHealth(), SetHealth(), InitHealth(), etc.
	ATTRIBUTE_ACCESSORS(ThisClass, Health);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);
	ATTRIBUTE_ACCESSORS(ThisClass, Power);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxPower);
};
