#pragma once
#include "BottomDweller/Controllers/PlayerInventoryController.h"

class ABottomDwellerPlayerController;
class UInventoryComponent;

class UUtils
{
public:
	static UPlayerInventoryController* GetInventorySubsystem(const UWorld* WorldContextObject);
	static UPlayerInventoryController* GetInventorySubsystem(const AActor* Actor);
	static ABottomDwellerPlayerController* GetPlayerController(const UWorld* World);
};
