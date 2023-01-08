// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class ABottomDwellerCharacter;

// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class BOTTOMDWELLER_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void OnInteract(AActor* Interactor) = 0;

	virtual FString GetInspectorDescription() const = 0;
};
