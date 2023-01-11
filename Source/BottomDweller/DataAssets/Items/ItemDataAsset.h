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

	UPROPERTY(EditDefaultsOnly, Category="Health")
	float MaxHealth;
	UPROPERTY(EditDefaultsOnly, Category=Health)
	float Health;
	UPROPERTY(EditDefaultsOnly, Category=Health)
	float HealthRegen;
	
	UPROPERTY(EditDefaultsOnly, Category=Stamina)
	float MaxStamina;
	UPROPERTY(EditDefaultsOnly, Category=Stamina)
	float Stamina;
	UPROPERTY(EditDefaultsOnly, Category=Stamina)
	float StaminaRegen;
	
	UPROPERTY(EditDefaultsOnly, Category=Mana)
	float MaxMana;
	UPROPERTY(EditDefaultsOnly, Category=Mana)
	float Mana;
	UPROPERTY(EditDefaultsOnly, Category=Mana)
	float ManaRegen;
	
	UPROPERTY(EditDefaultsOnly, Category=Attributes)
	float Dexterity;
	UPROPERTY(EditDefaultsOnly, Category=Attributes)
	float Strength;
	UPROPERTY(EditDefaultsOnly, Category=Attributes)
	float Intelligence;
	UPROPERTY(EditDefaultsOnly, Category=Attributes)
	float Luck;
	
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	float SlashingDamage;
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	float BluntDamage;
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	float PiercingDamage;
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
