// All rights reserved by Aboba Inc.


#include "TextEntry.h"

#include "Components/TextBlock.h"

void UTextEntry::SetProperty(FString Name, FString Value, FLinearColor Color) {
	PropertyName->SetText(FText::FromString(Name));
	PropertyValue->SetText(FText::FromString(Value));
	PropertyName->SetColorAndOpacity(Color);
	PropertyValue->SetColorAndOpacity(Color);
}

void UTextEntry::SetValue(FString Value) {
	PropertyValue->SetText(FText::FromString(Value));
}

void UTextEntry::SetName(FString Name) {
	PropertyName->SetText(FText::FromString(Name));
}

void UTextEntry::SetColor(FLinearColor Color) {
	PropertyName->SetColorAndOpacity(Color);
	PropertyValue->SetColorAndOpacity(Color);
}
