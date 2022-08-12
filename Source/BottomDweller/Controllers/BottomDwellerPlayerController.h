// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDwellerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API ABottomDwellerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;
};
