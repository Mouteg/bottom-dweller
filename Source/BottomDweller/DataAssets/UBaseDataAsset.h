// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UBaseDataAsset.generated.h"

UCLASS()
class BOTTOMDWELLER_API UBaseDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Id;
};
