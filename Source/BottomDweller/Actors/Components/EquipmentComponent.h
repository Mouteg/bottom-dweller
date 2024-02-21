// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"


class UGearItemDataAsset;
class UWeaponItemDataAsset;
class UItemDataAsset;
enum class EItemType : uint8;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOTTOMDWELLER_API UEquipmentComponent : public UActorComponent {
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentStateChange, UGearItemDataAsset*, Item, EItemType, Slot);

public:
	// Sets default values for this component's properties
	UEquipmentComponent();

	UFUNCTION(BlueprintCallable)
	void Equip(UGearItemDataAsset* Item);

	void Unequip(EItemType ItemType);

	UPROPERTY()
	FOnEquipmentStateChange OnEquipmentStateChange;

	FORCEINLINE TMap<EItemType, UGearItemDataAsset*> GetEquipmentState() const {
		return EquipmentState;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void ChangeEquipment(UGearItemDataAsset* Item);

	UPROPERTY(EditAnywhere)
	TMap<EItemType, UGearItemDataAsset*> EquipmentState;
};
