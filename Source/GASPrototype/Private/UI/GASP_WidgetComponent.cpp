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
	if (!BaseCharacter.IsValid()) return;

	if (!IsASCInitialized())
	{
		// ASC may not be ready yet on clients; defer until BaseCharacter signals initialization
		BaseCharacter->OnASCInitialized.AddUniqueDynamic(this, &ThisClass::OnASCInitialized);
		return;
	}

	InitializeAttributeDelegate();
}

void UGASP_WidgetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Unbind delegates before this WidgetComponent/Widget is destroyed
	ClearAttributeChangeDelegates();

	if (AttributeSet.IsValid())
	{
		AttributeSet->OnAttributesInitialized.RemoveDynamic(this, &ThisClass::BindToAttributeChanges);
	}

	if (BaseCharacter.IsValid())
	{
		BaseCharacter->OnASCInitialized.RemoveDynamic(this, &ThisClass::OnASCInitialized);
	}

	Super::EndPlay(EndPlayReason);
}

void UGASP_WidgetComponent::InitializeAbilitySystemData()
{
	// Attempt early initialization; may return null if ASC not yet ready
	BaseCharacter = Cast<AGASP_BaseCharacter>(GetOwner());
	if (!BaseCharacter.IsValid()) return;

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
		AttributeSet->OnAttributesInitialized.AddUniqueDynamic(this, &ThisClass::BindToAttributeChanges);
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
	// Avoid binding more than once; OnASCInitialized and OnAttributesInitialized may both call this
	if (bAttributeDelegatesBound) return;
	if (!IsASCInitialized() || !IsValid(GetUserWidgetObject())) return;

	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		// Bind the root widget and all child widgets that match this attribute pair
		BindWidgetsToAttributeChanges(GetUserWidgetObject(), Pair);

		// WidgetTree can be null if the WidgetComponent has no widget instance yet
		if (!IsValid(GetUserWidgetObject()->WidgetTree)) continue;

		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, Pair](UWidget* ChildWidget)
		{
			BindWidgetsToAttributeChanges(ChildWidget, Pair);
		});
	}

	bAttributeDelegatesBound = true;
}

void UGASP_WidgetComponent::BindWidgetsToAttributeChanges(UWidget* WidgetObject,
                                                          const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair)
{
	UGASP_AttributeWidget* AttributeWidget = Cast<UGASP_AttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget)) return;
	if (!AttributeWidget->MatchesAttribute(Pair)) return;
	AttributeWidget->AvatarActor = BaseCharacter;

	// Push initial values before any change event fires
	AttributeWidget->OnAttributeChanged(Pair, AttributeSet.Get(), 0.0f);

	// Register a delegate to keep the widget in sync on every subsequent change
	// Weak refs protect against callbacks fired by the PlayerState ASC after character switch
	const TWeakObjectPtr AttributeWidgetWeak = AttributeWidget;
	const TWeakObjectPtr<UGASP_AttributeSet> AttributeSetWeak = AttributeSet;
	const FDelegateHandle DelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda
	([AttributeWidgetWeak, AttributeSetWeak, Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		if (!AttributeWidgetWeak.IsValid() || !AttributeSetWeak.IsValid()) return;
		AttributeWidgetWeak->OnAttributeChanged(Pair, AttributeSetWeak.Get(), AttributeChangeData.OldValue);
	});
	AttributeChangeDelegateHandles.Emplace(Pair.Key, DelegateHandle);
}

void UGASP_WidgetComponent::ClearAttributeChangeDelegates()
{
	// Attribute delegates live on the ASC, which can outlive this pawn because it belongs to PlayerState
	if (AbilitySystemComponent.IsValid())
	{
		for (const TPair<FGameplayAttribute, FDelegateHandle>& AttributeChangeDelegateHandle : AttributeChangeDelegateHandles)
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeChangeDelegateHandle.Key).
				Remove(AttributeChangeDelegateHandle.Value);
		}
	}

	AttributeChangeDelegateHandles.Reset();
	bAttributeDelegatesBound = false;
} 
