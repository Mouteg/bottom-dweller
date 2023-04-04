// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"


class UWeaponItemDataAsset;
class UItemDataAsset;
enum class EItemType : uint8;

USTRUCT(BlueprintType)
struct FInventory_EquipmentState
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWeaponItemDataAsset> Weapon;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOTTOMDWELLER_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentStateChange, UItemDataAsset*, Item, EItemType, Slot);

public:
	// Sets default values for this component's properties
	UEquipmentComponent();

	UFUNCTION(BlueprintCallable)
	void Equip(UItemDataAsset* Item);

	UFUNCTION()
	FInventory_EquipmentState GetEquipmentState() const { return EquipmentState; }
	
	UPROPERTY()
	FOnEquipmentStateChange OnEquipmentStateChange;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void ChangeWeapon(UWeaponItemDataAsset* Item);
	UPROPERTY(EditAnywhere)
	FInventory_EquipmentState EquipmentState;
	TObjectPtr<UInventoryComponent> InventoryComponent;

};
