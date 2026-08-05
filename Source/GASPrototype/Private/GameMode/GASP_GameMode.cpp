// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GASP_GameMode.h"

#include "AbilitySystemComponent.h"
#include "Character/GASP_BaseCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "GameplayTags/GASP_CharacterTags.h"
#include "Kismet/GameplayStatics.h"
#include "Player/GASP_PlayerState.h"

UClass* AGASP_GameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	const AGASP_PlayerState* GASPPlayerState =
		InController ? InController->GetPlayerState<AGASP_PlayerState>() : nullptr;

	if (!IsValid(GASPPlayerState))
		return Super::GetDefaultPawnClassForController_Implementation(InController);

	const FGameplayTag SelectedCharacterTag = GASPPlayerState->GetSelectedCharacterTag();
	if (!SelectedCharacterTag.IsValid())
		return Super::GetDefaultPawnClassForController_Implementation(InController);
	
	
	if (SelectedCharacterTag.MatchesTagExact(GASPTags::Characters::Wukong) && Pawns.IsValidIndex(0))
	{
		return Pawns[0];
	}
	
	if (SelectedCharacterTag.MatchesTagExact(GASPTags::Characters::Phase) && Pawns.IsValidIndex(1))
	{
		return Pawns[1];
	}
	
	return DefaultPawnClass;
}

FVector AGASP_GameMode::GetRandomSpawnPoint()
{
	const UWorld* World = GetWorld();
	if (!IsValid(World)) return FVector::ZeroVector;

	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStarts);

	if (PlayerStarts.IsEmpty())
		return FVector::ZeroVector;

	const int32 Index = FMath::RandRange(0, PlayerStarts.Num() - 1);

	return PlayerStarts[Index]->GetActorLocation();
}

void AGASP_GameMode::SwitchCharacter(APlayerController* PlayerController)
{
	if (!IsValid(PlayerController) || Pawns.IsEmpty()) return;

	AGASP_BaseCharacter* OldCharacter = Cast<AGASP_BaseCharacter>(PlayerController->GetPawn());
	if (!IsValid(OldCharacter)) return;

	UAbilitySystemComponent* Asc = OldCharacter->GetAbilitySystemComponent();
	if (!IsValid(Asc)) return;

	//get next without repeat 
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
	if (Pawns.Num() > 1 && Pawns[CurrentPawnIndex] == OldCharacter->GetClass())
	{
		CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
	}
	const TSubclassOf<AGASP_BaseCharacter> NewCharacterClass = Pawns[CurrentPawnIndex];

	UWorld* World = GetWorld();
	if (!IsValid(World)) return;

	FVector OldForward = OldCharacter->GetActorForwardVector() * 150.f;
	FVector Location = OldCharacter->GetActorLocation() + (OldForward * -1);

	AGASP_BaseCharacter* NewCharacter = World->SpawnActor<AGASP_BaseCharacter>(
		NewCharacterClass,
		Location,
		OldCharacter->GetActorRotation());
	if (!IsValid(NewCharacter)) return;

	ResetASC(Asc);

	OldCharacter->Destroy();
	PlayerController->Possess(NewCharacter);
}

void AGASP_GameMode::ResetASC(UAbilitySystemComponent* Asc)
{
	if (!IsValid(Asc)) return;

	Asc->CancelAllAbilities();
	Asc->ClearAllAbilities();
	Asc->RemoveActiveEffects(FGameplayEffectQuery());
}
