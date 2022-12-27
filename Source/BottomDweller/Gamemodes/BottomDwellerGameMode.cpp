// Copyright Epic Games, Inc. All Rights Reserved.

#include "BottomDwellerGameMode.h"

#include "Engine/AssetManager.h"
#include "UObject/ConstructorHelpers.h"

ABottomDwellerGameMode::ABottomDwellerGameMode()
{
	// set default pawn class to our Blueprinted character
	
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BottomDweller/Actors/Player/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter"));
	// if (PlayerPawnBPClass.Class != NULL)
	// {
	// 	DefaultPawnClass = PlayerPawnBPClass.Class;
	// }
	
	// Load Assets bundles
	// TArray<FPrimaryAssetId> AssetIds;
	// TArray<FName> BundlesToLoad;
	// BundlesToLoad.Add(FName(TEXT("Items")));
	// UAssetManager::Get().LoadPrimaryAssets(AssetIds, BundlesToLoad);
}
