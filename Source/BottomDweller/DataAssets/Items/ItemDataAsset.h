﻿// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/DataAssets/BaseDataAsset.h"
#include "ItemDataAsset.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon UMETA(DisplayName = "Weapon"),
	Consumable UMETA(DisplayName = "Usable")
};

UCLASS(Abstract)
class BOTTOMDWELLER_API UItemDataAsset : public UBaseDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemType ItemType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AssetBundles="Items"))
	TSoftObjectPtr<UTexture2D> Thumbnail;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AssetBundles="Items"))
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "bIsStackable == true", EditConditionHides))
	int32 MaxStack;
};

//Maybe move inventory to BP_GameInstance
