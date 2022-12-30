// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Interactables/Interactable.h"
#include "GameFramework/Actor.h"
#include "InteractableItem.generated.h"

class UItemDataAsset;

UCLASS()
class BOTTOMDWELLER_API AInteractableItem : public AActor, public IInteractable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UItemDataAsset* InventoryItem;

	UPROPERTY()
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	int32 Quantity = 1;

	UPROPERTY(EditAnywhere)
	FString InspectorDescription = TEXT("Press E to pick up");


public:
	// Sets default values for this actor's properties
	AInteractableItem();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnInteract(ABottomDwellerCharacter* Interactor) override;

	UFUNCTION(BlueprintPure, BlueprintGetter, BlueprintCallable)
	virtual FString GetInspectorDescription() const override
	{
		return InspectorDescription;
	}
};
