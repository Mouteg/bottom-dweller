#include "InteractionComponent.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"


UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.05;
}

bool UInteractionComponent::TraceForInteractable(FHitResult& Hit) const
{
	const ABottomDwellerCharacter* OwnerCharacter = CastChecked<ABottomDwellerCharacter>(GetOwner());
	const FVector Start = OwnerCharacter->GetFollowCamera()->GetComponentLocation();
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

	if(GetWorld()->LineTraceSingleByChannel(
		OUT Hit,
		Start,
		End,
		ECC_GameTraceChannel1,
		CollisionParams
	))
	{
		return Hit.GetActor()->Implements<UInteractable>();
	}
	return false;
}

void UInteractionComponent::Interact(AActor* Interactor)
{
	FHitResult Hit;

	if (TraceForInteractable(OUT Hit))
	{
		IInteractable::Execute_OnInteract(Hit.GetActor(), Interactor);
		OnInteract.Broadcast(GetOwner());
	}
}

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
			OnInspect.Broadcast(IInteractable::Execute_GetInspectorDescription(Hit.GetActor()));
		}
		bIsInspecting = !bIsInspecting;
	}
}
