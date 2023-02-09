// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ComponentProviderSupport.generated.h"

class UBaseAbilitySystemComponent;
class UInventoryComponent;

UINTERFACE()
class UComponentProviderSupport : public UInterface
{
	GENERATED_BODY()
};

class BOTTOMDWELLER_API IComponentProviderSupport
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	UBaseAbilitySystemComponent* GetASCComponent();

	UFUNCTION(BlueprintNativeEvent)
	UInventoryComponent* GetInventoryComponent();

	UFUNCTION(BlueprintNativeEvent)
	UCharacterMovementComponent* GetPawnMovementComponent();
};
