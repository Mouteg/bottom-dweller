// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Maps/Interactable.h"
#include "BottomDweller/Saves/Saveable.h"
#include "GameFramework/Actor.h"
#include "ItemContainer.generated.h"

class UItemDataAsset;
UCLASS()
class BOTTOMDWELLER_API AItemContainer : public AActor, public IInteractable, public ISaveable
{
	GENERATED_BODY()
	
public:
	virtual void OnInteract_Implementation(AActor* Interactor) override;
	AItemContainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<TSoftObjectPtr<UItemDataAsset>, int32> Items;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UStaticMeshComponent> StaticMesh;
};
