// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayEffectTypes.h"
#include "InventoryComponent.generated.h"

class UEquipmentComponent;
class UItemDataAsset;
class UGameplayEffect;
class UWeaponItemDataAsset;
enum class EItemType : uint8;

//Enum -> struct -> class

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOTTOMDWELLER_API UInventoryComponent final : public UActorComponent {
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChange);

public:
	UInventoryComponent();
	TMap<TSoftObjectPtr<UItemDataAsset>, int32> GetInventoryContent() const { return InventoryContent; }

	UFUNCTION()
	int32 AddItem(UItemDataAsset* Item, const int32 Quantity = 1);

	UFUNCTION()
	void AddItems(UInventoryComponent* Inventory);

	UFUNCTION()
	void RemoveItem(const UItemDataAsset* Item, const int32 Quantity = 1);

	UFUNCTION()
	void UseItem(UItemDataAsset* Item, FGameplayEffectSpec& Spec);
	
	UFUNCTION()
	bool Contains(UItemDataAsset* Item, int Amount = 1, bool bExactAmount = false) const;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnChange OnChange;

	virtual void BeginPlay() override;

	UFUNCTION()
	void RemoveGameplayEffectSpec(EItemType Slot);

	// Add / remove
	// Sort
	// Transfer between two
	// Drag & drop

private:
	TMap<EItemType, FActiveGameplayEffectHandle> ActiveItemHandles;

	void ApplyGameplayEffectSpec(const FGameplayEffectSpec& Spec, const EItemType Slot);

	UPROPERTY()
	TMap<TSoftObjectPtr<UItemDataAsset>, int32> InventoryContent;
};
