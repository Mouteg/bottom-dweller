// All rights reserved by Aboba Inc.


#include "PlayerMenuWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Inventory/InventoryPanel.h"
#include "Inventory/InventoryUI.h"
#include "Stats/SimpleStatsWidget.h"

void UPlayerMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	WidgetSwitcher->AddChild(InventoryUI);
	WidgetSwitcher->AddChild(SimpleStatsWidget);

	WidgetMap.Add(EPlayerMenuScreen::Inventory, InventoryUI);
	WidgetMap.Add(EPlayerMenuScreen::Stats, SimpleStatsWidget);

	StatsButton->OnClicked.AddDynamic(this, &ThisClass::SetStatsActive);
	InventoryButton->OnClicked.AddDynamic(this, &ThisClass::SetInventoryActive);
}

void UPlayerMenuWidget::SetStatsActive()
{
	WidgetSwitcher->SetActiveWidget(SimpleStatsWidget);
}

void UPlayerMenuWidget::SetInventoryActive()
{
	WidgetSwitcher->SetActiveWidget(InventoryUI);
}

void UPlayerMenuWidget::SetActiveScreen(const EPlayerMenuScreen Screen)
{
	WidgetSwitcher->SetActiveWidget(WidgetMap.Find(Screen)->Get());
}

void UPlayerMenuWidget::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
	if (InVisibility == ESlateVisibility::Hidden)
	{
		InventoryUI->ContainerInventoryPanel->SetVisibility(InVisibility);
	}
}
