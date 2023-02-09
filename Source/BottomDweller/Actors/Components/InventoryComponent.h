// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "Components/ActorComponent.h"
#include "GameplayEffectTypes.h"
#include "InventoryComponent.generated.h"

class UGameplayEffect;
class UWeaponItemDataAsset;

//Enum -> struct -> class

UENUM(BlueprintType)
enum class EGearSlots : uint8
{
	Weapon,
	None,
};

USTRUCT(BlueprintType)
struct FInventory_EquipmentState
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWeaponItemDataAsset> Weapon;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOTTOMDWELLER_API UInventoryComponent final : public UActorComponent
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChange);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentStateChange, UItemDataAsset*, Item, EGearSlots, Slot);
	
public:
	UInventoryComponent();

	UFUNCTION()
	FInventory_EquipmentState GetEquipmentState() const { return EquipmentState; }
	TMap<TSoftObjectPtr<UItemDataAsset>, int32> GetInventoryContent() const { return InventoryContent; }

	UFUNCTION(BlueprintCallable)
	int32 AddItem(UItemDataAsset* Item, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(const UItemDataAsset* Item, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	void UseItem(UItemDataAsset* Item, FGameplayEffectSpec& Spec);

	UFUNCTION(BlueprintCallable)
	void Equip(UItemDataAsset* Item, EGearSlots Slot);
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnChange OnChange;

	UPROPERTY()
	FOnEquipmentStateChange OnEquipmentStateChange;
	// Add / remove
	// Sort
	// Transfer between two
	// Drag & drop
	
private:
	TMap<EGearSlots, FActiveGameplayEffectHandle> ActiveItemHandles;
	
	void ChangeWeapon(UWeaponItemDataAsset* Item);

	void ApplyGameplayEffectSpec(const FGameplayEffectSpec& Spec, const EGearSlots Slot);
	
	UPROPERTY(EditAnywhere)
	FInventory_EquipmentState EquipmentState;

	UPROPERTY()
	TMap<TSoftObjectPtr<UItemDataAsset>, int32> InventoryContent;

};
