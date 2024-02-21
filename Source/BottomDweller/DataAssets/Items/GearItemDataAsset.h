// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataAsset.h"
#include "GearItemDataAsset.generated.h"

UCLASS()
class BOTTOMDWELLER_API UGearItemDataAsset : public UItemDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AssetBundles="Items"))
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override {
		return FPrimaryAssetId(TEXT("GearItem"), GetFName());
	}
};
