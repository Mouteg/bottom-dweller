﻿// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Maps/Interactable.h"
#include "BottomDweller/Saves/Saveable.h"
#include "GameFramework/Actor.h"
#include "InteractableItem.generated.h"

class UItemDataAsset;

UCLASS()
class BOTTOMDWELLER_API AInteractableItem : public AActor, public IInteractable, public ISaveable {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableItem();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void OnInteract_Implementation(AActor* Interactor) override;
	virtual FString GetInspectorDescription_Implementation() const override;
	FORCEINLINE virtual bool CanInteract_Implementation() override { return true; }

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UItemDataAsset> InventoryItem;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, SaveGame)
	int32 Quantity = 1;

	UPROPERTY(EditAnywhere)
	FString InspectorDescription = TEXT("Press E to pick up");
};
