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
class BOTTOMDWELLER_API UInventoryComponent final : public UActorComponent
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChange);
	
public:
	UInventoryComponent();
	TMap<TSoftObjectPtr<UItemDataAsset>, int32> GetInventoryContent() const { return InventoryContent; }

	UFUNCTION(BlueprintCallable)
	int32 AddItem(UItemDataAsset* Item, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(const UItemDataAsset* Item, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	void UseItem(UItemDataAsset* Item, FGameplayEffectSpec& Spec);
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnChange OnChange;
	
	virtual void BeginPlay() override;

	// Add / remove
	// Sort
	// Transfer between two
	// Drag & drop
	
private:
	TMap<EItemType, FActiveGameplayEffectHandle> ActiveItemHandles;
	
	void ApplyGameplayEffectSpec(const FGameplayEffectSpec& Spec, const EItemType Slot);

	UPROPERTY()
	TMap<TSoftObjectPtr<UItemDataAsset>, int32> InventoryContent;

	TObjectPtr<UEquipmentComponent> EquipmentComponent;

};
