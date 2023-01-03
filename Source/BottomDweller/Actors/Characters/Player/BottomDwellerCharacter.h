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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, ABottomDwellerCharacter*, Interactor);

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

protected:
	/** Called for movement input */
	UFUNCTION(BlueprintCallable)
	void Move(float ForwardValue, float RightValue);

	virtual void BeginPlay() override;
	
public:

	UPROPERTY(EditAnywhere)
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere)
	float AttackWalkSpeed;
	
	ABottomDwellerCharacter();

	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintPure, BlueprintCallable, BlueprintGetter)
	UInventoryComponent* GetInventoryComponent() const
	{
		return InventoryComponent;
	}

	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(BlueprintAssignable)
	FOnInteract OnInteract;

	virtual void BeginAttack() override;
	virtual void EndAttack() override;
	virtual void EnableWeaponCollision() override;
	virtual void DisableWeaponCollision() override;
};
