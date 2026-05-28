// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GASP_WidgetComponent.h"

#include "AbilitySystem/GASP_AbilitySystemComponent.h"
#include "AbilitySystem/GASP_AttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Character/GASP_BaseCharacter.h"
#include "UI/GASP_AttributeWidget.h"


UGASP_WidgetComponent::UGASP_WidgetComponent()
{
}


void UGASP_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeAbilitySystemData();
	if (!IsASCInitialized())
	{
		// ASC may not be ready yet on clients; defer until BaseCharacter signals initialization
		BaseCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
		return;
	}

	InitializeAttributeDelegate();
}

void UGASP_WidgetComponent::InitializeAbilitySystemData()
{
	// Attempt early initialization; may return null if ASC not yet ready
	BaseCharacter = Cast<AGASP_BaseCharacter>(GetOwner());
	AbilitySystemComponent = Cast<UGASP_AbilitySystemComponent>(BaseCharacter->GetAbilitySystemComponent());
	AttributeSet = Cast<UGASP_AttributeSet>(BaseCharacter->GetAttributeSet());
}

bool UGASP_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UGASP_WidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		// Attributes are populated by the first GE application; wait for that before binding
		AttributeSet->OnAttributesInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}


void UGASP_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UGASP_AbilitySystemComponent>(ASC);
	AttributeSet = Cast<UGASP_AttributeSet>(AS);

	// Attributes are populated by the first GE application; guard against arriving before that
	if (!IsASCInitialized()) return;
	InitializeAttributeDelegate();
}

void UGASP_WidgetComponent::BindToAttributeChanges()
{
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		// Bind the root widget and all child widgets that match this attribute pair
		BindWidgetsToAttributeChanges(GetUserWidgetObject(), Pair);

		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			BindWidgetsToAttributeChanges(ChildWidget, Pair);
		});
	}
}

void UGASP_WidgetComponent::BindWidgetsToAttributeChanges(UWidget* WidgetObject,
                                                          const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair)
const
{
	UGASP_AttributeWidget* AttributeWidget = Cast<UGASP_AttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget)) return;
	if (!AttributeWidget->MatchesAttribute(Pair)) return;
	AttributeWidget->AvatarActor = BaseCharacter;

	// Push initial values before any change event fires
	AttributeWidget->OnAttributeChanged(Pair, AttributeSet.Get(), 0.0f);

	// Register a delegate to keep the widget in sync on every subsequent change
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda
	([this, AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChanged(Pair, AttributeSet.Get(), AttributeChangeData.OldValue);
	});
}
