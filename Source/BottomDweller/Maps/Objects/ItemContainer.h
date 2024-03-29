﻿// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UnlockableActor.h"
#include "BottomDweller/Maps/Interactable.h"
#include "BottomDweller/Saves/Saveable.h"
#include "GameFramework/Actor.h"
#include "ItemContainer.generated.h"

class UInventoryComponent;
class UItemDataAsset;

UCLASS()
class BOTTOMDWELLER_API AItemContainer : public AUnlockableActor, public ISaveable {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UFUNCTION(BlueprintGetter)
	FString GetContainerName() const {
		return ContainerName;
	}

	UFUNCTION(BlueprintSetter)
	void SetContainerName(const FString Name) {
		ContainerName = Name;
	}

	virtual void OnInteract_Implementation(AActor* Interactor) override;
	AItemContainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY()
	FString ContainerName;
};
