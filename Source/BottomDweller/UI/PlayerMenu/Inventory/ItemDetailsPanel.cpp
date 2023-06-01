// All rights reserved by Aboba Inc.


#include "ItemDetailsPanel.h"

#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

bool UItemDetailsPanel::Initialize()
{
	bool bSuccess = Super::Initialize();
	this->SetVisibility(ESlateVisibility::Hidden);
	return bSuccess;
}

void UItemDetailsPanel::LoadDetails(UItemDataAsset* Item)
{
	if (!Item)
	{
		return;
	}
	
	if (Item->Thumbnail.Get())
	{
		Thumbnail->SetBrushFromTexture(Item->Thumbnail.Get());
	}
	
	DisplayName->SetText(FText::FromName(Item->DisplayName));
	Description->SetText(Item->Description);
	LoadItemProperties(Item);
}

void UItemDetailsPanel::LoadItemProperties(UItemDataAsset* Item)
{
	PropertiesContainer->ClearChildren();
	UTextEntry* Entry = CreateWidget<UTextEntry>(this, DetailsEntryWidget);
	//Make an enum of default props ?
	PropertiesContainer->AddChild(Entry);
	CreateDetailsEntries(Item->ItemStatEffect);
	Entry->SetProperty("Cost", FString::FromInt(Item->Cost), FLinearColor::Yellow);
}

void UItemDetailsPanel::CreateDetailsEntries(FItemStatEffect StatEffect)
{
	for (TFieldIterator<FProperty> Property(StatEffect.StaticStruct()); Property; ++Property)
	{
		const float Value = *Property->ContainerPtrToValuePtr<float>(&StatEffect);
		if (Value != 0)
		{
			UTextEntry* Entry = CreateWidget<UTextEntry>(this, DetailsEntryWidget);
			Entry->SetProperty(Property->GetName(), "+" + FString::FromInt(Value), FLinearColor::MakeRandomSeededColor(GetTypeHash(Property->GetName())));
			PropertiesContainer->AddChild(Entry);
		}
	}
}
