// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStack;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChange);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOTTOMDWELLER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UDataTable* ItemsTable;

	int32 MaxSize;

	bool CheckItemExists(const FName ItemName) const;

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	FOnChange OnChange;

	UPROPERTY(BlueprintReadWrite)
	TMap<FName, int32> InventoryContent;

	UFUNCTION()
	bool AddItem(FName ItemName, const int32 Quantity);

	UFUNCTION()
	void RemoveItem(const FName ItemName, const int32 Quantity);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
