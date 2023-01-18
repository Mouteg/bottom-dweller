// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/DataAssets/BaseDataAsset.h"
#include "ItemDataAsset.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Gear UMETA(DisplayName = "Gear"),
	Consumable UMETA(DisplayName = "Usable")
};

USTRUCT(BlueprintType)
struct FItemStatEffect
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category=Health)
	float MaxHealth = 0;
	UPROPERTY(EditDefaultsOnly, Category=Health)
	float Health = 0;
	UPROPERTY(EditDefaultsOnly, Category=Health)
	float HealthRegen = 0;
	
	UPROPERTY(EditDefaultsOnly, Category=Stamina)
	float MaxStamina = 0;
	UPROPERTY(EditDefaultsOnly, Category=Stamina)
	float Stamina = 0;
	UPROPERTY(EditDefaultsOnly, Category=Stamina)
	float StaminaRegen = 0;
	
	UPROPERTY(EditDefaultsOnly, Category=Mana)
	float MaxMana = 0;
	UPROPERTY(EditDefaultsOnly, Category=Mana)
	float Mana = 0;
	UPROPERTY(EditDefaultsOnly, Category=Mana)
	float ManaRegen = 0;
	
	UPROPERTY(EditDefaultsOnly, Category=Attributes)
	float Dexterity = 0;
	UPROPERTY(EditDefaultsOnly, Category=Attributes)
	float Strength = 0;
	UPROPERTY(EditDefaultsOnly, Category=Attributes)
	float Intelligence = 0;
	UPROPERTY(EditDefaultsOnly, Category=Attributes)
	float Luck = 0;
	
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	float SlashingDamage = 0;
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	float BluntDamage = 0;
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	float PiercingDamage = 0;
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
	FItemStatEffect ItemStatEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "bIsStackable == true", EditConditionHides))
	int32 MaxStack;
};

//Maybe move inventory to BP_GameInstance
