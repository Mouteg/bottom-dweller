// All rights reserved by Aboba Inc.


#include "UnlockableActor.h"

#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "BottomDweller/Util/UUtils.h"


// Sets default values
AUnlockableActor::AUnlockableActor() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Only refrains to unlocking by IActivatable
	bIsLocked = true;
	bConsumesItems = true;
}

void AUnlockableActor::Activate_Implementation() {
	bIsLocked = false;
}

bool AUnlockableActor::CanInteract_Implementation() {
	if (ItemsToUnlock.Num() == 0 || !bIsLocked) {
		return true;
	}
	
	UPlayerInventoryController* PlayerInventoryController = UUtils::GetInventorySubsystem(GetWorld());
	for (auto [Item, Amount, ExactAmount] : ItemsToUnlock) {
		if (!PlayerInventoryController->Contains(
				Item.Get(),
				Amount,
				ExactAmount
			)
		) {
			return false;
		}
	}

	if (bConsumesItems) {
		for (auto [Item, Amount, ExactAmount] : ItemsToUnlock) {
			PlayerInventoryController->RemoveItem(Item.Get(), Amount);
		}
	}
	return true;
}
