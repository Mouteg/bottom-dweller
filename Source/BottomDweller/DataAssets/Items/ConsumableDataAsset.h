// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UItemDataAsset.h"
#include "ConsumableDataAsset.generated.h"


UCLASS()
class BOTTOMDWELLER_API UConsumableDataAsset : public UItemDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HealAmount;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("Consumable"), GetFName());
	}
};
