// Copyright Epic Games, Inc. All Rights Reserved.

#include "BottomDwellerGameMode.h"

#include "BottomDweller/Actors/Characters/Abilities/BottomDwellerAbilitySystemGlobals.h"
#include "Engine/AssetManager.h"

ABottomDwellerGameMode::ABottomDwellerGameMode()
{
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BottomDweller/Actors/Player/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter"));
	// if (PlayerPawnBPClass.Class != NULL)
	// {
	// 	DefaultPawnClass = PlayerPawnBPClass.Class;
	// }
}

void ABottomDwellerGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<FPrimaryAssetId> AssetIds;
	TArray<FName> BundlesToLoad;
	BundlesToLoad.Add(FName(TEXT("Items")));
	UAssetManager::Get().GetPrimaryAssetIdList(FPrimaryAssetType(TEXT("WeaponItem")), AssetIds);
	UAssetManager::Get().GetPrimaryAssetIdList(FPrimaryAssetType(TEXT("Usableitem")), AssetIds);
	UAssetManager::Get().GetPrimaryAssetIdList(FPrimaryAssetType(TEXT("WeaponAnimations")), AssetIds);
	UAssetManager::Get().LoadPrimaryAssets(AssetIds, BundlesToLoad);

	UBottomDwellerAbilitySystemGlobals::Get().InitGlobalData();
}
