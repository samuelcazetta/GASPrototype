#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "GASP_BaseCharacter.generated.h"

struct FOnAttributeChangeData;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UGASP_GameplayAbility;

//Data container for hit reaction effects
USTRUCT(BlueprintType)
struct FHitReactContainer
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> Montage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USoundBase> Sound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UParticleSystem> Particle;
};

//Delegate for telling UI that ASC and AttributeSet are initialized
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*,
                                             AttributeSet);

UCLASS(Abstract)
class GASPROTOTYPE_API AGASP_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASP_BaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const;

	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized; //Delegate for telling UI that ASC is initialized

	/**
	 * This function implements a slight Hack 'n Slash like combo mechanic within GAS.
	 * Input starts or continues sequences:
	 * Tries primary ability (opener); falls back to secondary (combo chain) if primary fails.
	 * If no combo is intended, just PrimaryTag is needed.
	 * 
	 * @param PrimaryTag The primary gameplay tag for the ability.
	 * @param SecondaryTag The secondary gameplay tag for fallback ability. Only for combo Abilities.
	 */
	void ActivateAbility(const FGameplayTag& PrimaryTag, const FGameplayTag& SecondaryTag = FGameplayTag());
	
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;
	
	bool IsMovementBlocked() const;
	bool IsTangible() const;
	bool IsAlive() const;
	
	UFUNCTION(BlueprintCallable, Category = "GASP|Death")
	void ResetAttributes();

protected:
	//virtual void BeginPlay() override;

	void GiveStartupAbilities();
	void InitializeAttributes();
	
	void OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData);
	virtual void HandleDeath();

private:
	UPROPERTY(EditDefaultsOnly, Category = "GASP|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities; //Abilities BPs, not Objects

	UPROPERTY(EditDefaultsOnly, Category = "GASP|Effects")
	TSubclassOf<UGameplayEffect> InitialAttributesEffect;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASP|HitReact")
	FHitReactContainer HitReactContainer;
};
