// All rights reserved by Aboba Inc.


#include "SaveGameManager.h"

#include "BottomDwellerSaveGame.h"
#include "EngineUtils.h"
#include "Saveable.h"
#include "SaveGameSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void USaveGameManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const USaveGameSettings* SaveSettings = GetDefault<USaveGameSettings>();
	CurrentSlotName = SaveSettings->SaveSlotName;
}

void USaveGameManager::SetSlotName(FString NewSlotName)
{
	// Ignore empty name
	if (NewSlotName.Len() == 0)
	{
		return;
	}
	
	CurrentSlotName = NewSlotName;
}

void USaveGameManager::WriteSaveGame(FString SlotName)
{
	SetSlotName(SlotName);
	if (!CurrentSaveGame)
	{
		CurrentSaveGame = Cast<UBottomDwellerSaveGame>(UGameplayStatics::CreateSaveGameObject(UBottomDwellerSaveGame::StaticClass()));
	}
	CurrentSaveGame->SavedActors.Empty();
	
	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (GameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to write SaveGame Data."));
		return;
	}
	
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (!IsValid(Actor) || !Actor->Implements<USaveable>())
		{
			continue;
		}
		
		FActorSaveData ActorData;
		ActorData.ActorName = Actor->GetFName();
		ActorData.Transform = Actor->GetActorTransform();

		FMemoryWriter MemWriter(ActorData.ByteData);

		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		Ar.ArIsSaveGame = true;
		Actor->Serialize(Ar);

		CurrentSaveGame->SavedActors.Add(ActorData);
	}
	
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, CurrentSlotName, 0);
}

void USaveGameManager::LoadSaveGame(FString SlotName)
{
	SetSlotName(SlotName);
	
	if (!UGameplayStatics::DoesSaveGameExist(CurrentSlotName, 0))
	{
		CurrentSaveGame = Cast<UBottomDwellerSaveGame>(UGameplayStatics::CreateSaveGameObject(UBottomDwellerSaveGame::StaticClass()));
		return;
	}

	
	CurrentSaveGame = Cast<UBottomDwellerSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentSlotName, 0));
	if (!CurrentSaveGame)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load SaveGame Data."));
		return;
	}

	// Array of actors that dont exist inside save game
	TArray<AActor*> ActorsToDestroy;
	
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (!Actor->Implements<USaveable>())
		{
			continue;
		}

		bool ActorExists = false;
		
		for (FActorSaveData ActorData : CurrentSaveGame->SavedActors)
		{
			if (ActorData.ActorName == Actor->GetFName())
			{
				ActorExists = true;
				Actor->SetActorTransform(ActorData.Transform);

				// FMemoryReader MemReader(ActorData.ByteData);
				//
				// FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
				// Ar.ArIsSaveGame = true;
				// Actor->Serialize(Ar);
				
				ISaveable::Execute_OnActorLoaded(Actor);
				break;
			}
		}
		if (!ActorExists)
		{
			ActorsToDestroy.Add(Actor);
		}
	}

	for (AActor* ToDestroy : ActorsToDestroy)
	{
		ToDestroy->Destroy();
	}
}
