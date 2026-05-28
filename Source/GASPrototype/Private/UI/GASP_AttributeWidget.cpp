// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GASP_AttributeWidget.h"
#include "AbilitySystem/GASP_AttributeSet.h"

void UGASP_AttributeWidget::OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair,
                                               const UGASP_AttributeSet* AttributeSet, const float OldValue)
{
	const float AttributeValue = Pair.Key.GetNumericValue(AttributeSet); 
	const float MaxAttributeValue = Pair.Value.GetNumericValue(AttributeSet);
	
	BP_OnAttributechanged(AttributeValue, MaxAttributeValue, OldValue);
}

bool UGASP_AttributeWidget::MatchesAttribute(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	return Attribute == Pair.Key && MaxAttribute == Pair.Value;
}
