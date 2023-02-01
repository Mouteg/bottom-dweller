// All rights reserved by Aboba Inc.


#include "SimpleStatsWidget.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/UI/PlayerMenu/Inventory/ItemDetailsEntry.h"
#include "Components/VerticalBox.h"

void USimpleStatsWidget::InitDelegates()
{
	TArray<FGameplayAttribute> OutAttributes;
	UBaseAbilitySystemComponent* ASC = Cast<ABottomDwellerCharacter>(GetOwningPlayerPawn())->GetAbilitySystemComponent();

	if (!ASC) return;

	ASC->GetAllAttributes(OutAttributes);
	for (const FGameplayAttribute Attribute : OutAttributes)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &USimpleStatsWidget::UpdateStats);
		Attributes.Add(Attribute.AttributeName, ASC->GetNumericAttribute(Attribute));
	}
}

void USimpleStatsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitDelegates();
}

void USimpleStatsWidget::UpdateStats(const FOnAttributeChangeData& Data)
{
	StatsContainer->ClearChildren();

	if(Attributes.Contains(Data.Attribute.AttributeName))
	{
		Attributes[Data.Attribute.AttributeName] = Data.NewValue;
	}
	else
	{
		return;
	}

	for (TTuple<FString, float> Attribute : Attributes)
	{
		const FString Value = FString::FromInt(static_cast<int32>(Attribute.Value));
		UItemDetailsEntry* AttributeEntry = CreateWidget<UItemDetailsEntry>(this, EntryWidget);
		AttributeEntry->SetProperty(Attribute.Key, Value, FLinearColor::MakeRandomSeededColor(GetTypeHash(Attribute.Key)));
		StatsContainer->AddChildToVerticalBox(AttributeEntry);
	}
}
