#pragma once

#include "GameplayEffect.h"
#include "GearItemDataAsset.h"
#include "ItemDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "WeaponItemDataAsset.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	OneHanded_Sword UMETA(DisplayName = "One-Handed Sword"),
};

UCLASS()
class BOTTOMDWELLER_API UWeaponItemDataAsset : public UItemDataAsset, public IGearItemDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponType WeaponType;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("WeaponItem"), GetFName());
	}
};
