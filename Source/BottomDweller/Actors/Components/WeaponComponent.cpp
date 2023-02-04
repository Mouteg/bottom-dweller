// All rights reserved by Aboba Inc.


#include "WeaponComponent.h"

#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bCanTrace = false;
	bDrawDebug = false;
}


void UWeaponComponent::SetCanTrace(bool CanTrace)
{
	bCanTrace = CanTrace;
	if (bCanTrace)
	{
		HitArray.Empty();
	}
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bCanTrace && !Sockets.IsEmpty())
	{
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(GetOwner());

		for (FName Socket : Sockets)
		{
			FVector Start;
			if (SocketLocations.Contains(Socket))
			{
				Start = SocketLocations[Socket];
			}
			else
			{
				break;
			}
			const FVector End = GetSocketLocation(Socket);
			TArray<FHitResult> OutHits;

			const EDrawDebugTrace::Type DrawDebugType = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
			UKismetSystemLibrary::LineTraceMulti(
				GetWorld(),
				Start,
				End,
				UEngineTypes::ConvertToTraceType(ECC_Visibility),
				false,
				ActorsToIgnore,
				DrawDebugType,
				OutHits,
				true
			);
			AddToHitArray(OutHits);
		}
	}
	UpdateLastKnowSocketLocations();
}

void UWeaponComponent::SetSkeletalMesh(USkeletalMesh* NewMesh, bool bReinitPose)
{
	Super::SetSkeletalMesh(NewMesh, bReinitPose);
	Sockets = GetAllSocketNames();
}

void UWeaponComponent::UpdateLastKnowSocketLocations()
{
	for (FName Socket : Sockets)
	{
		SocketLocations.Add(Socket, GetSocketLocation(Socket));
	}
}

void UWeaponComponent::AddToHitArray(TArray<FHitResult> HitArrayToAdd)
{
	for (const FHitResult& Hit : HitArrayToAdd)
	{
		if (!HitArray.ContainsByPredicate([&](const FHitResult& Inner) {  return Inner.GetActor() == Hit.GetActor(); }))
		{
			HitArray.Add(Hit);
			OnHit.Broadcast(Hit);
		}
	}
}
