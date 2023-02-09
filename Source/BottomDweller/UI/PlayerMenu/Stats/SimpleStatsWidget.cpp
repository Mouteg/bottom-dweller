// All rights reserved by Aboba Inc.


#include "SimpleStatsWidget.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Characters/Player/PlayerAttributeSet.h"
#include "BottomDweller/UI/PlayerMenu/Inventory/TextEntry.h"
#include "Components/VerticalBox.h"

void USimpleStatsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeDelegates();
	InitializeAttributes();
}

void USimpleStatsWidget::InitializeDelegates()
{
	TArray<FGameplayAttribute> OutAttributes;
	UBaseAbilitySystemComponent* ASC = IComponentProviderSupport::Execute_GetASCComponent(GetOwningPlayerPawn());

	if (!ASC) return;

	ASC->GetAllAttributes(OutAttributes);
	for (const FGameplayAttribute Attribute : OutAttributes)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &ThisClass::UpdateStats);
		Attributes.Add(Attribute.AttributeName, ASC->GetNumericAttribute(Attribute));
	}
}

void USimpleStatsWidget::InitializeAttributes()
{
	DefaultAttributes.Add(UPlayerAttributeSet::GetStrengthAttribute().AttributeName);
	DefaultAttributes.Add(UPlayerAttributeSet::GetDexterityAttribute().AttributeName);
	DefaultAttributes.Add(UPlayerAttributeSet::GetIntelligenceAttribute().AttributeName);
	DefaultAttributes.Add(UPlayerAttributeSet::GetLuckAttribute().AttributeName);
	
	DefaultAttributes.Add(UBaseAttributeSet::GetBluntDamageAttribute().AttributeName);
	DefaultAttributes.Add(UBaseAttributeSet::GetSlashingDamageAttribute().AttributeName);
	DefaultAttributes.Add(UBaseAttributeSet::GetPiercingDamageAttribute().AttributeName);
	
	DefaultAttributes.Add(UBaseAttributeSet::GetBluntDamageResistanceAttribute().AttributeName);
	DefaultAttributes.Add(UBaseAttributeSet::GetSlashingDamageResistanceAttribute().AttributeName);
	DefaultAttributes.Add(UBaseAttributeSet::GetPiercingDamageResistanceAttribute().AttributeName);

	HealthComposite.ValueAttribute = UBaseAttributeSet::GetHealthAttribute().AttributeName;
	HealthComposite.MaxValueAttribute = UBaseAttributeSet::GetMaxHealthAttribute().AttributeName;
	HealthComposite.RegenValueAttribute = UBaseAttributeSet::GetHealthRegenAttribute().AttributeName;

	StaminaComposite.ValueAttribute = UPlayerAttributeSet::GetStaminaAttribute().AttributeName;
	StaminaComposite.MaxValueAttribute = UPlayerAttributeSet::GetMaxStaminaAttribute().AttributeName;
	StaminaComposite.RegenValueAttribute = UPlayerAttributeSet::GetStaminaRegenAttribute().AttributeName;

	ManaComposite.ValueAttribute = UPlayerAttributeSet::GetManaAttribute().AttributeName;
	ManaComposite.MaxValueAttribute = UPlayerAttributeSet::GetMaxManaAttribute().AttributeName;
	ManaComposite.RegenValueAttribute = UPlayerAttributeSet::GetManaRegenAttribute().AttributeName;
}

void USimpleStatsWidget::UpdateStats(const FOnAttributeChangeData& Data)
{
	if (!Attributes.Contains(Data.Attribute.AttributeName))
	{
		return;
	}

	Attributes[Data.Attribute.AttributeName] = Data.NewValue;

	if (!bIsInitialized)
	{
		CreateEntries();
		bIsInitialized = true;
		return;
	}
	UpdateEntry(Data.Attribute.AttributeName);
}

void USimpleStatsWidget::CreateEntries()
{
	if (!IsValid(EntryWidget))
	{
		return;
	}

	int32 Index = 0;
	CreateOrUpdateCompositeEntry(HealthComposite, Index);
	Index++;

	CreateOrUpdateCompositeEntry(StaminaComposite, Index);
	Index++;

	CreateOrUpdateCompositeEntry(ManaComposite, Index);
	Index++;
	
	for (TTuple<FString, int32> Attribute : Attributes)
	{
		if (!DefaultAttributes.Contains(Attribute.Key))
		{
			continue;
		}

		UTextEntry* AttributeEntry = CreateWidget<UTextEntry>(this, EntryWidget);
		AttributeEntry->SetProperty(Attribute.Key, FString::FromInt(Attribute.Value), FLinearColor::MakeRandomSeededColor(GetTypeHash(Attribute.Key)));
		StatsContainer->AddChildToVerticalBox(AttributeEntry);
		AttributeToChildIndex.Add(Attribute.Key, Index);
		Index++;
	}
}

void USimpleStatsWidget::CreateOrUpdateCompositeEntry(const FCompositeEntryAttributes& CompositeAttributes, const int32 Index)
{
	UTextEntry* AttributeEntry = nullptr;
	if (AttributeToChildIndex.Contains(CompositeAttributes.ValueAttribute))
	{
		AttributeEntry = Cast<UTextEntry>(StatsContainer->GetChildAt(AttributeToChildIndex[CompositeAttributes.ValueAttribute]));
	}

	if (!IsValid(AttributeEntry))
	{
		AttributeEntry = CreateWidget<UTextEntry>(this, EntryWidget);
		StatsContainer->AddChildToVerticalBox(AttributeEntry);

		AttributeToChildIndex.Add(CompositeAttributes.ValueAttribute, Index);
		AttributeToChildIndex.Add(CompositeAttributes.MaxValueAttribute, Index);
		AttributeToChildIndex.Add(CompositeAttributes.RegenValueAttribute, Index);
	}
	const FString StringValue = FString::Format(
		TEXT("{0}/{1} +{2}"),
		{
			Attributes[CompositeAttributes.ValueAttribute],
			Attributes[CompositeAttributes.MaxValueAttribute],
			Attributes[CompositeAttributes.RegenValueAttribute]
		}
	);
	AttributeEntry->SetProperty(CompositeAttributes.ValueAttribute, StringValue,
	                            FLinearColor::MakeRandomSeededColor(GetTypeHash(CompositeAttributes.ValueAttribute)));
}

void USimpleStatsWidget::UpdateEntry(const FString& AttributeName)
{
	if (!AttributeToChildIndex.Contains(AttributeName))
	{
		return;
	}
	
	UTextEntry* Entry = Cast<UTextEntry>(StatsContainer->GetChildAt(AttributeToChildIndex[AttributeName]));
	if (IsValid(Entry))
	{
		if (DefaultAttributes.Contains(AttributeName))
		{
			Entry->SetValue(FString::FromInt(Attributes[AttributeName]));
			return;
		}

		if (AttributeName.Contains(HealthComposite.ValueAttribute))
		{
			CreateOrUpdateCompositeEntry(HealthComposite);
		}

		if (AttributeName.Contains(StaminaComposite.ValueAttribute))
		{
			CreateOrUpdateCompositeEntry(StaminaComposite);
		}

		if (AttributeName.Contains(ManaComposite.ValueAttribute))
		{
			CreateOrUpdateCompositeEntry(ManaComposite);
		}
	}
}
