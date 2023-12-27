#pragma once
#include "BottomDweller/Controllers/PlayerInventoryController.h"

class UInventoryComponent;

class UUtils
{
public:
	static UPlayerInventoryController* GetInventorySubsystem(const UWorld* WorldContextObject);
	static UPlayerInventoryController* GetInventorySubsystem(const AActor* Actor);
};
