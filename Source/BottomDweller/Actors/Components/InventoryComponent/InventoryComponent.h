// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChange);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOTTOMDWELLER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnChange OnChange;

	UPROPERTY(BlueprintReadWrite)
	TMap<TSoftObjectPtr<UItemDataAsset>, int32> InventoryContent;

	UFUNCTION()
	int32 AddItem(UItemDataAsset* Item, const int32 Quantity);

	UFUNCTION()
	void RemoveItem(const UItemDataAsset* Item, const int32 Quantity);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Add / remove
	// Sort
	// Transfer between two
	// Drag & drop
};
