// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class ABottomDwellerCharacter;

// Turn on StaticMesh->SetRenderCustomDepth(true); for outlines to work
UINTERFACE(BlueprintType, Blueprintable)
class UInteractable : public UInterface {
	GENERATED_BODY()
};

class BOTTOMDWELLER_API IInteractable {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnInteract(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent)
	FString GetInspectorDescription() const;

	UFUNCTION(BlueprintNativeEvent)
    bool CanInteract();
};
