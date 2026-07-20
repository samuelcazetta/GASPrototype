// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GASP_AttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UGASP_AttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME_CONDITION_NOTIFY(UGASP_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASP_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASP_AttributeSet, Power, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASP_AttributeSet, MaxPower, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME(ThisClass, bAttributesInitialized);
}

void UGASP_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// clamp to max health and mana if GE exceds max values
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetPowerAttribute())
	{
		SetPower(FMath::Clamp(GetPower(), 0.f, GetMaxPower()));
	}

	// Broadcast attribute initialization for UI
	if (!bAttributesInitialized)
	{
		bAttributesInitialized = true;
		OnAttributesInitialized.Broadcast();
	}
}

void UGASP_AttributeSet::OnRep_AttributesInitialized()
{
	// Broadcast attribute initialization for UI
	if (bAttributesInitialized)
	{
		OnAttributesInitialized.Broadcast();
	}
}

void UGASP_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldValue);
}

void UGASP_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldValue);
}

void UGASP_AttributeSet::OnRep_Power(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Power, OldValue);
}

void UGASP_AttributeSet::OnRep_MaxPower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxPower, OldValue);
}
