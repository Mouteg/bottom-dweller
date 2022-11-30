// All rights reserved by Aboba Inc.


#include "ItemDetailsEntry.h"

#include "Components/TextBlock.h"

void UItemDetailsEntry::SetProperty(FString Name, FString Value, FLinearColor Color) const
{
	PropertyName->SetText(FText::FromString(Name));
	PropertyValue->SetText(FText::FromString(Value));
	PropertyName->SetColorAndOpacity(Color);
	PropertyValue->SetColorAndOpacity(Color);
}
