#include "InteractionComponent.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Interactables/Interactable.h"
#include "GameFramework/Character.h"


UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	ABottomDwellerCharacter* OwnerCharacter = CastChecked<ABottomDwellerCharacter>(GetOwner());
	OwnerCharacter->OnInteract.AddDynamic(this, &UInteractionComponent::Interact);
}

void UInteractionComponent::Interact(ABottomDwellerCharacter* Interactor)
{
	FHitResult Hit;

	if (TraceForInteractable(OUT Hit))
	{
		if (IInteractable* Interactable = ToInteractable(Hit))
		{
			Interactable->OnInteract(Interactor);
		}
	}
}

bool UInteractionComponent::TraceForInteractable(FHitResult& Hit) const
{
	const ACharacter* OwnerCharacter = CastChecked<ACharacter>(GetOwner());
	FVector Start = OwnerCharacter->GetActorLocation();
	Start.Z += TraceStartZOffset;
	const FVector CameraRotationVector = OwnerCharacter->GetControlRotation().Vector();
	const FVector End = Start + Length * CameraRotationVector;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	// DrawDebugLine(
	// 	GetWorld(),
	// 	Start,
	// 	End,
	// 	FColor::Red,
	// 	false,
	// 	1,
	// 	1,
	// 	3
	// );

	return GetWorld()->LineTraceSingleByChannel(
		OUT Hit,
		Start,
		End,
		ECC_GameTraceChannel1,
		CollisionParams
	);
}

// Make in timer ?
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult Hit;
	if (TraceForInteractable(OUT Hit) != bIsInspecting)
	{
		if (bIsInspecting)
		{
			OnStopInspecting.Broadcast();
		}
		else
		{
			if (const IInteractable* Interactable = ToInteractable(Hit))
			{
				OnInspect.Broadcast(Interactable->GetInspectorDescription());
			}
		}
		bIsInspecting = !bIsInspecting;
	}
}
