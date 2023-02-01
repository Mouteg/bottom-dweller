// Copyright Epic Games, Inc. All Rights Reserved.

#include "BottomDwellerGameMode.h"

#include "BottomDweller/Actors/Characters/Abilities/BottomDwellerAbilitySystemGlobals.h"
#include "BottomDweller/Saves/SaveGameManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"

void ABottomDwellerGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	LoadPrimaryAssets();
	
	UBottomDwellerAbilitySystemGlobals::Get().InitGlobalData();
	USaveGameManager* SaveGameManager = GetGameInstance()->GetSubsystem<USaveGameManager>();
	FString SelectedSaveSlot = UGameplayStatics::ParseOption(Options, "SaveGame");
	SaveGameManager->LoadSaveGame("SaveGame01");
}

ABottomDwellerGameMode::ABottomDwellerGameMode()
{
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BottomDweller/Actors/Player/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter"));
	// if (PlayerPawnBPClass.Class != NULL)
	// {
	// 	DefaultPawnClass = PlayerPawnBPClass.Class;
	// }
}

void ABottomDwellerGameMode::LoadPrimaryAssets()
{
	TArray<FPrimaryAssetId> AssetIds;
	TArray<FName> BundlesToLoad;
	BundlesToLoad.Add(FName(TEXT("Items")));
	UAssetManager::Get().GetPrimaryAssetIdList(FPrimaryAssetType(TEXT("WeaponItem")), AssetIds);
	UAssetManager::Get().GetPrimaryAssetIdList(FPrimaryAssetType(TEXT("Usableitem")), AssetIds);
	UAssetManager::Get().GetPrimaryAssetIdList(FPrimaryAssetType(TEXT("WeaponAnimations")), AssetIds);
	UAssetManager::Get().LoadPrimaryAssets(AssetIds, BundlesToLoad);
}
