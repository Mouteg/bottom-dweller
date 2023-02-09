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
	UBaseAbilitySystemComponent* GetASCComponent() const;

	UFUNCTION(BlueprintNativeEvent)
	UInventoryComponent* GetInventoryComponent() const;

	UFUNCTION(BlueprintNativeEvent)
	UCharacterMovementComponent* GetPawnMovementComponent() const;
};
