// All rights reserved by Aboba Inc.


#include "ItemDetailsPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UItemDetailsPanel::LoadDetails(UItemDataAsset* Item)
{
	Thumbnail->SetBrushFromTexture(Item->Thumbnail.Get());
	DisplayName->SetText(FText::FromName(Item->DisplayName));
	Description->SetText(Item->Description);
	LoadItemProperties(Item);
}

bool UItemDetailsPanel::Initialize()
{
	bool bSuccess = Super::Initialize();
	this->SetVisibility(ESlateVisibility::Hidden);
	return bSuccess;
}

void UItemDetailsPanel::LoadItemProperties(UItemDataAsset* Item)
{
	PropertiesContainer->ClearChildren();
	UItemDetailsEntry* Entry = CreateWidget<UItemDetailsEntry>(this, DetailsEntryWidget);
	//Make an enum of default props ?
	Entry->SetProperty("Cost", FString::SanitizeFloat(Item->Cost), FLinearColor::Yellow);
	PropertiesContainer->AddChild(Entry);
}
