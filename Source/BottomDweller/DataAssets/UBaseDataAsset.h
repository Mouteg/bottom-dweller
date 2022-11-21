// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UBaseDataAsset.generated.h"

UENUM(BlueprintType)
enum class EAssetId : uint8
{
	Stone UMETA(DisplayName = "Stone"),
	Stick UMETA(DisplayName = "Stick")
};

UCLASS()
class BOTTOMDWELLER_API UBaseDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAssetId Id;
};
