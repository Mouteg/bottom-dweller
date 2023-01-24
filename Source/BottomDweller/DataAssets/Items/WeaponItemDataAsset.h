#pragma once

#include "GearItemDataAsset.h"
#include "ItemDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "WeaponItemDataAsset.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	OneHanded_Sword UMETA(DisplayName = "One-Handed Sword"),
	TwoHanded_Sword UMETA(DisplayName = "One-Handed Sword"),
	OneHanded_Axe UMETA(DisplayName = "Two-Handed Axe"),
	TwoHanded_Axe UMETA(DisplayName = "Two-Handed Axe"),
};

UCLASS()
class BOTTOMDWELLER_API UWeaponItemDataAsset : public UGearItemDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponType WeaponType;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("WeaponItem"), GetFName());
	}
};
