﻿#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, AActor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInspect, FString, Description);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopInspecting);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class BOTTOMDWELLER_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* LastHitActor;

	UFUNCTION()
	bool TraceForInteractable(FHitResult& Hit) const;

	void SetOutlineStencilOnLastHitActor(bool Value);

public:
	// Sets default values for this component's properties
	UInteractionComponent();
	
	UFUNCTION()
	void Interact(AActor* Interactor);
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsInspecting = false;

	/** Length of interactor */
	UPROPERTY(EditAnywhere)
	float Length = 500.f;

	UPROPERTY(BlueprintAssignable)
	FOnInteract OnInteract;

	UPROPERTY(BlueprintAssignable)
	FOnInspect OnInspect;
	
	UPROPERTY(BlueprintAssignable)
	FOnStopInspecting OnStopInspecting;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};