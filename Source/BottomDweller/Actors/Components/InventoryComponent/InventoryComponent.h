// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventory_EquipmentState
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	class UWeaponItemDataAsset* Weapon;
};

UENUM(BlueprintType)
enum class EGearSlots : uint8
{
	Weapon,
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentStateChange, UItemDataAsset*, Item, EGearSlots, Slot);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOTTOMDWELLER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FInventory_EquipmentState EquipmentState;

	UPROPERTY()
	TMap<TSoftObjectPtr<UItemDataAsset>, int32> InventoryContent;

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION()
	FInventory_EquipmentState GetEquipmentState() const { return EquipmentState; }
	TMap<TSoftObjectPtr<UItemDataAsset>, int32> GetInventoryContent() const { return InventoryContent; }

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnChange OnChange;

	UPROPERTY()
	FOnEquipmentStateChange OnEquipmentStateChange;

	UFUNCTION(BlueprintCallable)
	int32 AddItem(UItemDataAsset* Item, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(const UItemDataAsset* Item, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	void UseItem(UItemDataAsset* Item);

	UFUNCTION(BlueprintCallable)
	void Equip(UItemDataAsset* Item, EGearSlots Slot);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Add / remove
	// Sort
	// Transfer between two
	// Drag & drop
};
