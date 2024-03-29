﻿// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UnlockableActor.h"
#include "PressurePlate.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API APressurePlate : public AUnlockableActor {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	APressurePlate();

	UPROPERTY(EditAnywhere)
	bool bOneTimeUse;

	UPROPERTY(EditAnywhere)
	bool bIsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> ObjectsToActivate;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere)
	FString InspectorDescription;

	UFUNCTION()
	void OnOverlap(AActor* ActorOverlapped, AActor* OtherActor);

	virtual void OnInteract_Implementation(AActor* Interactor) override;
	virtual FString GetInspectorDescription_Implementation() const override;

private:
	UPROPERTY()
	bool bIsUsed = false;
};
