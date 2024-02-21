// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BottomDwellerHUD.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API ABottomDwellerHUD final : public AHUD {
	GENERATED_BODY()

public:
	ABottomDwellerHUD();
	void InitializeHUD();
	bool IsMenuVisible() const;
	void SetGameMenuVisible();
	void SetGameMenuHidden();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerMenuWidgetSwitcherClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> PlayerMenuWidgetSwitcher;
};
