// All rights reserved by Aboba Inc.


#include "SaveGameManager.h"

#include "BottomDwellerSaveGame.h"
#include "EngineUtils.h"
#include "Saveable.h"
#include "SaveGameSettings.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

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
		// Find only variables with UPROPERTY(SaveGame)
		Ar.ArIsSaveGame = true;
		// Converts Actor's SaveGame UPROPERTIES into binary array
		Actor->Serialize(Ar);

		CurrentSaveGame->SavedActors.Add(ActorData);
	}
	
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, CurrentSlotName, 0);
}

void USaveGameManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const USaveGameSettings* SaveSettings = GetDefault<USaveGameSettings>();
	CurrentSlotName = SaveSettings->SaveSlotName;
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
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (!Actor->Implements<USaveable>())
		{
			continue;
		}

		for (FActorSaveData ActorData : CurrentSaveGame->SavedActors)
		{
			if (ActorData.ActorName == Actor->GetFName())
			{
				Actor->SetActorTransform(ActorData.Transform);
				UE_LOG(LogTemp, Warning, TEXT("Actor: %s, %d"), *Actor->GetName(), ActorData.ByteData.Num());

				FMemoryReader MemReader(ActorData.ByteData);
				
				FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
				Ar.ArIsSaveGame = true;
				Actor->Serialize(Ar);

				if (ABottomDwellerCharacter* PlayerCharacter = Cast<ABottomDwellerCharacter>(Actor))
				{
					PlayerCharacter->SetInventoryComponent(PlayerCharacter->GetInventoryComponent());
				}
				
				ISaveable::Execute_OnActorLoaded(Actor);
				break;
			}
		}
	}
}
