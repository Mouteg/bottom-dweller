// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Components/EquipmentComponent.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerInventoryController.generated.h"

class UInventoryComponent;
/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UPlayerInventoryController : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Deinitialize() override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void Equip(UItemDataAsset* Item);

	UFUNCTION()
	FInventory_EquipmentState GetEquipmentState() const { return EquipmentComponent->GetEquipmentState(); }

	UFUNCTION()
	TMap<TSoftObjectPtr<UItemDataAsset>, int32> GetInventoryContent() const { return InventoryComponent->GetInventoryContent(); }

	UFUNCTION(BlueprintCallable)
	int32 AddItem(UItemDataAsset* Item, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(const UItemDataAsset* Item, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	void UseItem(UItemDataAsset* Item, FGameplayEffectSpec& Spec);

	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY()
	TObjectPtr<UEquipmentComponent> EquipmentComponent;
};
