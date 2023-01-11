// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "Components/ActorComponent.h"
#include "GameplayEffectTypes.h"
#include "InventoryComponent.generated.h"

class UGameplayEffect;

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
	
	TMap<EGearSlots, FActiveGameplayEffectHandle> ActiveItemHandles;
	
	void ChangeWeapon(UWeaponItemDataAsset* Item);

	void ApplyGameplayEffectSpec(const FGameplayEffectSpec& Spec);
	
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
};
