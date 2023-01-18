// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "PressurePlate.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UPressurePlate : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPressurePlate();
	
	UPROPERTY(EditDefaultsOnly)
	class ATriggerBox* TriggerBox;

	void OnOverlap(AActor* ActorOverlapped, AActor* OtherActor);
};
