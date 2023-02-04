#include "InteractionComponent.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Maps/Interactable.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"


UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.05;
	bDrawDebug = false;
}

bool UInteractionComponent::TraceForInteractable(FHitResult& Hit) const
{
	const ABottomDwellerCharacter* OwnerCharacter = CastChecked<ABottomDwellerCharacter>(GetOwner());
	const FVector Start = OwnerCharacter->GetFollowCamera()->GetComponentLocation();
	const FVector CameraRotationVector = OwnerCharacter->GetControlRotation().Vector();
	const FVector End = Start + Length * CameraRotationVector;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	if (bDrawDebug)
	{
		DrawDebugLine(
			GetWorld(),
			Start,
			End,
			FColor::Red,
			false,
			1,
			1,
			3
		);
	}

	if (GetWorld()->LineTraceSingleByChannel(
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
	// Condition for bIsInspecting needed so that if we already inspect we dont trace again
	if (TraceForInteractable(OUT Hit) != bIsInspecting)
	{
		if (bIsInspecting)
		{
			OnStopInspecting.Broadcast();
			if (LastHitActor)
			{
				SetOutlineStencilOnLastHitActor(false);
				LastHitActor = nullptr;
			}
		}
		else
		{
			LastHitActor = Hit.GetActor();
			OnInspect.Broadcast(IInteractable::Execute_GetInspectorDescription(Hit.GetActor()));
			SetOutlineStencilOnLastHitActor(true);
		}
		bIsInspecting = !bIsInspecting;
	}
}

void UInteractionComponent::SetOutlineStencilOnLastHitActor(bool Value)
{
	if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(LastHitActor->GetComponentByClass(UStaticMeshComponent::StaticClass())))
	{
		if (Value)
		{
			//TODO Magic numbers -> to config
			Mesh->SetCustomDepthStencilValue(1);
		}
		else
		{
			Mesh->SetCustomDepthStencilValue(0);
		}
	}
}