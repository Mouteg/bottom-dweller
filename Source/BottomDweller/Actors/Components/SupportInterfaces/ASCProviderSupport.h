// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ASCProviderSupport.generated.h"

class UEquipmentComponent;
class UBaseAbilitySystemComponent;
class UInventoryComponent;

UINTERFACE()
class UASCProviderSupport : public UInterface {
	GENERATED_BODY()
};

class BOTTOMDWELLER_API IASCProviderSupport {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	UBaseAbilitySystemComponent* GetASCComponent() const;
};
