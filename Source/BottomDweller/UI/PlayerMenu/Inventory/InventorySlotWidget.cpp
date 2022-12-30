// All rights reserved by Aboba Inc.


#include "InventorySlotWidget.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent/InventoryComponent.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"

bool UInventorySlotWidget::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	return bSuccess;
}

void UInventorySlotWidget::SetOwner(UInventoryPanel* OwnerWidget)
{
	Owner = OwnerWidget;
}

void UInventorySlotWidget::SetItem(UItemDataAsset* InventoryItem, int32 ItemQuantity)
{
	Item = InventoryItem;
	Quantity = ItemQuantity;
	
	if (UTexture2D* ItemThumbnail = Item->Thumbnail.Get())
	{
		Thumbnail->SetBrushFromTexture(ItemThumbnail);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant load item thumbnail"));
	}
	QuantityText->SetText(FText::AsNumber(Quantity));
}

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (Owner)
	{
		Thumbnail->SetRenderOpacity(0.5);
		Owner->OnHover.Execute(Item);
	}
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	if (Owner)
	{
		Thumbnail->SetRenderOpacity(1);
		Owner->OnUnHover.Execute();
	}
}

FReply UInventorySlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	const FGameplayTag UseItemTag = FGameplayTag::RequestGameplayTag(FName("Event.UseItem"));
	FGameplayEventData EventData;
	EventData.OptionalObject = Item;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner->InventoryComponent->GetOwner(), UseItemTag, EventData);
	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}
