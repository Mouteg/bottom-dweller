// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataAsset.h"
#include "UsableItemDataAsset.generated.h"

class UGameplayEffect;

UCLASS()
class BOTTOMDWELLER_API UUsableItemDataAsset : public UItemDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsInfinite;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override {
		return FPrimaryAssetId(TEXT("UsableItem"), GetFName());
	}
};
