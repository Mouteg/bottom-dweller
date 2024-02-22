// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Components/EquipmentComponent.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
#include "BottomDweller/Maps/Objects/UnlockableActor.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerInventoryController.generated.h"

class UInventoryPanel;
class UInventoryComponent;
/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UPlayerInventoryController : public UGameInstanceSubsystem {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag UseItemEventTag;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UInventoryPanel> ContainerInventoryPanel;

	FORCEINLINE virtual void Deinitialize() override;
	FORCEINLINE virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	FORCEINLINE void OpenContainer(const TObjectPtr<UInventoryComponent> ContainerInventoryComponent, const FString& ContainerName);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void Equip(UGearItemDataAsset* Item);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void Unequip(EItemType Slot);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TMap<EItemType, UGearItemDataAsset*> GetEquipmentState() const {
		return EquipmentComponent->GetEquipmentState();
	}

	UFUNCTION()
	FORCEINLINE TMap<TSoftObjectPtr<UItemDataAsset>, int32> GetInventoryContent() const { return InventoryComponent->GetInventoryContent(); }

	// Adds item, returns how many was added
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 AddItem(UItemDataAsset* Item, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void AddItems(UInventoryComponent* Inventory);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RemoveItem(const UItemDataAsset* Item, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void UseItem(UItemDataAsset* Item);

	UFUNCTION()
	FORCEINLINE void InitSubsystem(UInventoryComponent* Inventory, UEquipmentComponent* Equipment) {
		InventoryComponent = Inventory;
		EquipmentComponent = Equipment;
	}

	UFUNCTION()
	FORCEINLINE UInventoryPanel* GetContainerInventoryPanel() const {
		return ContainerInventoryPanel;
	}

	UFUNCTION()
	FORCEINLINE UInventoryComponent* GetInventoryComponent() const {
		return InventoryComponent;
	}

	UFUNCTION()
	FORCEINLINE UEquipmentComponent* GetEquipmentComponent() const {
		return EquipmentComponent;
	}

	FORCEINLINE void SetContainerInventoryPanel(const TObjectPtr<UInventoryPanel> Inventory) {
		ContainerInventoryPanel = Inventory;
	}

	FORCEINLINE bool Contains(UItemDataAsset* Item, const int Amount = 1, const bool bExactAmount = false) const;

private:
	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY()
	TObjectPtr<UEquipmentComponent> EquipmentComponent;

public:
};
