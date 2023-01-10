// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/BaseCharacter.h"
#include "BottomDweller/Actors/Characters/MeleeAttacker.h"
#include "BottomDwellerCharacter.generated.h"

class UItemDataAsset;
class ABottomDwellerCharacter;
struct FInventory_EquipmentState;

typedef TFunction<void (UItemDataAsset*)> FEquipFunc;

UCLASS(config=Game)
class ABottomDwellerCharacter : public ABaseCharacter, public IMeleeAttacker
{
	GENERATED_BODY()
	
	void InitActorComponents();
	void InitEquipFunctions();
	
	UFUNCTION(BlueprintCallable)
	void OnEquipmentStateChange(UItemDataAsset* Item, EGearSlots Slot);
	FEquipFunc ChangeWeapon();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeaponComponent;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	TMap<EGearSlots, FEquipFunc> EquipFunctions;

	TMap<EGearSlots, FActiveGameplayEffectHandle> ActiveItemHandles;
	
protected:
	/** Called for movement input */
	UFUNCTION(BlueprintCallable)
	void Move(float ForwardValue, float RightValue);

	virtual void BeginPlay() override;
	
public:

	UPROPERTY(EditAnywhere, Category="Walking")
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere)
	FRotator RotationRate;
	
	UPROPERTY(EditAnywhere)
	float AttackWalkSpeed;

	UPROPERTY(EditAnywhere)
	FRotator AttackRotationRate;
	
	ABottomDwellerCharacter();

	UFUNCTION(BlueprintPure, BlueprintCallable, BlueprintGetter)
	UInventoryComponent* GetInventoryComponent() const
	{
		return InventoryComponent;
	}
	
	UFUNCTION(BlueprintPure, BlueprintCallable, BlueprintGetter)
	UInteractionComponent* GetInteractionComponent() const
	{
		return InteractionComponent;
	}

	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void BeginAttack() override;
	virtual void EndAttack() override;
	virtual void EnableWeaponCollision() override;
	virtual void DisableWeaponCollision() override;
};
