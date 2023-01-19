// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "PressurePlate.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API APressurePlate : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:

	APressurePlate();
	
	UPROPERTY(EditAnywhere)
	bool bOneTimeUse;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> ObjectsToActivate;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;

	UFUNCTION()
	void OnOverlap(AActor* ActorOverlapped, AActor* OtherActor);
};
