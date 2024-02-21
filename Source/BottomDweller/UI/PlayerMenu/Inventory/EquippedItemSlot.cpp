// All rights reserved by Aboba Inc.


#include "EquippedItemSlot.h"

#include "BottomDweller/Util/UUtils.h"

FReply UEquippedItemSlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	if (IsValid(Item)) {
		UUtils::GetInventorySubsystem(GetWorld())->Unequip(Item->ItemType);
	}
	return FReply::Handled();
}
