// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryComponentProvider.generated.h"

UINTERFACE()
class UInventoryComponentProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOTTOMDWELLER_API IInventoryComponentProvider
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	UInventoryComponent* GetInventoryComponent() const;
};
