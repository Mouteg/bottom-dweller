// All rights reserved by Aboba Inc.


#include "BottomDwellerHUD.h"

#include "Blueprint/UserWidget.h"

ABottomDwellerHUD::ABottomDwellerHUD()
{
}

void ABottomDwellerHUD::InitializeHUD()
{
	if (IsValid(HUDClass))
	{
		UUserWidget* HUD = CreateWidget(GetOwningPlayerController(), HUDClass);
		HUD->AddToViewport();
	}


	if (IsValid(PlayerMenuWidgetSwitcherClass))
	{
		PlayerMenuWidgetSwitcher = CreateWidget(GetOwningPlayerController(), PlayerMenuWidgetSwitcherClass);
		PlayerMenuWidgetSwitcher->AddToViewport();
		PlayerMenuWidgetSwitcher->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool ABottomDwellerHUD::IsMenuVisible() const
{
	return PlayerMenuWidgetSwitcher->IsVisible();
}

void ABottomDwellerHUD::SetGameMenuVisible()
{
	PlayerMenuWidgetSwitcher->SetVisibility(ESlateVisibility::Visible);
	
}

void ABottomDwellerHUD::SetGameMenuHidden()
{
	PlayerMenuWidgetSwitcher->SetVisibility(ESlateVisibility::Hidden);
}
