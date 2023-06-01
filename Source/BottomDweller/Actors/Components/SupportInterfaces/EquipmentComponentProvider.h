// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EquipmentComponentProvider.generated.h"

UINTERFACE()
class UEquipmentComponentProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOTTOMDWELLER_API IEquipmentComponentProvider
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	UEquipmentComponent* GetEquipmentComponent() const;
};
