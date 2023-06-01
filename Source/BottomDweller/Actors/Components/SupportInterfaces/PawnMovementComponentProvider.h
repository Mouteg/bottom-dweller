// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnMovementComponentProvider.generated.h"

class UCharacterMovementComponent;
UINTERFACE()
class UPawnMovementComponentProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOTTOMDWELLER_API IPawnMovementComponentProvider
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	UCharacterMovementComponent* GetPawnMovementComponent() const;
};
