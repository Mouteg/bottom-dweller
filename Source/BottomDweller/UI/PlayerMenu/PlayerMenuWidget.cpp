// All rights reserved by Aboba Inc.


#include "PlayerMenuWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Inventory/InventoryUI.h"
#include "Stats/SimpleStatsWidget.h"

void UPlayerMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	WidgetSwitcher->AddChild(InventoryUI);
	WidgetSwitcher->AddChild(SimpleStatsWidget);
	
	StatsButton->OnClicked.AddDynamic(this, &UPlayerMenuWidget::SetStatsActive);
	InventoryButton->OnClicked.AddDynamic(this, &UPlayerMenuWidget::SetInventoryActive);
}


void UPlayerMenuWidget::SetStatsActive()
{
	WidgetSwitcher->SetActiveWidget(SimpleStatsWidget);
}

void UPlayerMenuWidget::SetInventoryActive()
{
	WidgetSwitcher->SetActiveWidget(InventoryUI);
}
