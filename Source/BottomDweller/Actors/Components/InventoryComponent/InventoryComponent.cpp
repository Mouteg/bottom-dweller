// All rights reserved by Aboba Inc.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool UInventoryComponent::AddItem(const FName ItemName, const int32 Quantity)
{
	//TODO Add support for stackable
	if (!CheckItemExists(ItemName))
	{
		UE_LOG(LogTemp, Error, TEXT("No such item with name - %s"), *ItemName.ToString())
		return false;
	}

	if (InventoryContent.Contains(ItemName))
	{
		InventoryContent[ItemName] += Quantity;
	}
	else
	{
		InventoryContent.Add(ItemName, Quantity);
	}
	OnChange.Broadcast();
	return true;
}

void UInventoryComponent::RemoveItem(const FName ItemName, const int32 Quantity)
{
	if (InventoryContent.Contains(ItemName) && InventoryContent[ItemName] > Quantity)
	{
		InventoryContent[ItemName] -= Quantity;
	}
	else
	{
		InventoryContent.Remove(ItemName);
	}
	OnChange.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Item removed %s"), *ItemName.ToString())
}

bool UInventoryComponent::CheckItemExists(const FName ItemName) const
{
	return ItemsTable->FindRow<FInventoryItem>(FName(ItemName), TEXT("")) != nullptr;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}
