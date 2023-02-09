// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventorySupport.generated.h"

class UInventoryComponent;
// This class does not need to be modified.
UINTERFACE()
class UInventorySupport : public UInterface
{
	GENERATED_BODY()
};

class BOTTOMDWELLER_API IInventorySupport
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	UInventoryComponent* GetInventoryComponent();
};
