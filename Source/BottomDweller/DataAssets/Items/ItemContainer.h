// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Components/SupportInterfaces/InventoryComponentProvider.h"
#include "BottomDweller/Maps/Interactable.h"
#include "BottomDweller/Saves/Saveable.h"
#include "GameFramework/Actor.h"
#include "ItemContainer.generated.h"

class UInventoryComponent;
class UItemDataAsset;
UCLASS()
class BOTTOMDWELLER_API AItemContainer : public AActor, public IInteractable, public ISaveable, public IInventoryComponentProvider
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UFUNCTION(BlueprintPure, BlueprintCallable, BlueprintGetter)
	virtual UInventoryComponent* GetInventoryComponent_Implementation() const override
	{
		return InventoryComponent;
	}
	
	virtual void OnInteract_Implementation(AActor* Interactor) override;
	AItemContainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UInventoryComponent> InventoryComponent;
};
