// All rights reserved by Aboba Inc.


#include "BottomDwellerPlayerController.h"
#include "Blueprint/UserWidget.h"

void ABottomDwellerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UUserWidget* HUD = CreateWidget(this, HUDClass))
	{
		HUD->AddToViewport();
	}
}
