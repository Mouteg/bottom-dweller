// All rights reserved by Aboba Inc.


#include "PressurePlate.h"

#include "BottomDweller/Maps/Activatable.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerBox.h"

APressurePlate::APressurePlate() {
	bOneTimeUse = false;
	bIsButton = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Plate collision"));
	SetRootComponent(BoxComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plate Mesh"));
	MeshComponent->SetupAttachment(BoxComponent);
	MeshComponent->SetRenderCustomDepth(true);
	MeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
}

void APressurePlate::BeginPlay() {
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
}

void APressurePlate::OnOverlap(AActor* ActorOverlapped, AActor* OtherActor) {
	for (AActor* Actor : ObjectsToActivate) {
		if (Actor->Implements<UActivatable>()) {
			//play sound, maybe animation
			IActivatable::Execute_Activate(Actor);
		}
	}
	if (bOneTimeUse) {
		Destroy();
	}
}

void APressurePlate::OnInteract_Implementation(AActor* Interactor) {
	if (bIsButton) {
		OnOverlap(this, Interactor);
	}
}

FString APressurePlate::GetInspectorDescription_Implementation() const {
	if (bIsButton) {
		return InspectorDescription;
	}
	return TEXT("");
}
