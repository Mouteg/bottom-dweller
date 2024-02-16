#include "UUtils.h"

#include "BottomDweller/Controllers/BottomDwellerPlayerController.h"
#include "BottomDweller/Controllers/PlayerInventoryController.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"


UPlayerInventoryController* UUtils::GetInventorySubsystem(const UWorld* WorldContextObject)
{
	return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UPlayerInventoryController>();
}

UPlayerInventoryController* UUtils::GetInventorySubsystem(const AActor* Actor)
{
	return GetInventorySubsystem(Actor->GetWorld());
}

ABottomDwellerPlayerController* UUtils::GetPlayerController(const UWorld* World)
{
	return Cast<ABottomDwellerPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
}

UItemDataAsset* UUtils::GetItemDataAsset(const FString& ItemName)
{
	return Cast<UItemDataAsset>(UAssetManager::Get().GetPrimaryAssetObject(FPrimaryAssetId(ItemName)));
}
