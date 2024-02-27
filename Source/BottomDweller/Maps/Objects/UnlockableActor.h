// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Maps/Activatable.h"
#include "BottomDweller/Maps/Interactable.h"
#include "GameFramework/Actor.h"
#include "UnlockableActor.generated.h"

class UItemDataAsset;

USTRUCT(BlueprintType)
struct FItemRequirement {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UItemDataAsset> Item;
	UPROPERTY(EditAnywhere)
	int Amount = 1;
	UPROPERTY(EditAnywhere)
	bool ExactAmount = false;
};

UCLASS(Abstract)
class BOTTOMDWELLER_API AUnlockableActor : public AActor, public IInteractable, public IActivatable {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUnlockableActor();
	virtual void Activate_Implementation() override;
	virtual bool CanInteract_Implementation() override;

	UPROPERTY(EditAnywhere)
	TArray<FItemRequirement> ItemsToUnlock;

	UPROPERTY(EditAnywhere)
	bool bIsLocked;

	UPROPERTY(EditAnywhere)
	bool bConsumesItems;
};
