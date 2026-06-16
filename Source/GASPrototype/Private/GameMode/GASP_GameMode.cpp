// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GASP_GameMode.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

FVector AGASP_GameMode::GetRandomSpawnPoint()
{
	const UWorld* World = GetWorld();
	if (!IsValid(World)) return FVector::ZeroVector;
	
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(World,APlayerStart::StaticClass(),PlayerStarts);
	
	if (PlayerStarts.IsEmpty())	
		return FVector::ZeroVector;
	
	const int32 Index = FMath::RandRange(0, PlayerStarts.Num() - 1);
	
	return PlayerStarts[Index]->GetActorLocation();
}
