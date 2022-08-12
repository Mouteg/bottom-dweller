// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOTTOMDWELLER_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnInteract(ABottomDwellerCharacter* Interactor) = 0;

	virtual FString GetInspectorDescription() const = 0;
};
