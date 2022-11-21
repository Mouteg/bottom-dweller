#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Interactables/Interactable.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInspect, FString, Description);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopInspecting);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class BOTTOMDWELLER_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	bool bIsInspecting = false;

	UPROPERTY(EditAnywhere)
	float TraceStartZOffset = 75.f;

	UFUNCTION()
	void Interact(ABottomDwellerCharacter* Interactor);

	UFUNCTION()
	bool TraceForInteractable(FHitResult& Hit) const;

	IInteractable* ToInteractable(const FHitResult Hit) const
	{
		return Cast<IInteractable>(Hit.GetActor());
	}

public:
	// Sets default values for this component's properties
	UInteractionComponent();


	/** Length of interactor */
	UPROPERTY(EditAnywhere)
	float Length = 500.f;

	FOnInspect OnInspect;
	FOnStopInspecting OnStopInspecting;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
