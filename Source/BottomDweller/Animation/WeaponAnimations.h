// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "WeaponAnimations.generated.h"

enum class EWeaponType : uint8;
class UWeaponItemDataAsset;

USTRUCT()
struct FWeaponTypeAnimations
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(AssetBundles="Items"))
	TArray<TSoftObjectPtr<UAnimMontage>> AnimMontages;
};

UCLASS(BlueprintType)
class BOTTOMDWELLER_API UWeaponAnimations : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:
	//TODO: Possibly many copies of AnimMontages
	UPROPERTY(EditDefaultsOnly)
	TMap<EWeaponType, FWeaponTypeAnimations> WeaponTypeAnimations;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("WeaponAnimations"), GetFName());
	}
	
private:
	UPROPERTY(EditDefaultsOnly, meta=(AssetBundles="Items"))
	TArray<TSoftObjectPtr<UAnimMontage>> AnimMontages;
};
