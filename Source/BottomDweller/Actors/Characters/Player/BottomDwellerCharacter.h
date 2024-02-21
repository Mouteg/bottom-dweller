// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/BaseCharacter.h"
#include "BottomDweller/Actors/Characters/MeleeAttacker.h"
#include "BottomDweller/Actors/Components/SupportInterfaces/PawnMovementComponentProvider.h"
#include "BottomDwellerCharacter.generated.h"

class UInteractionComponent;
class UPointLightComponent;
class UCameraComponent;
class UInventoryComponent;

UCLASS(config=Game)
class ABottomDwellerCharacter :
	public ABaseCharacter,
	public IMeleeAttacker,
	public IPawnMovementComponentProvider {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float WalkSpeed;

	UPROPERTY(EditAnywhere)
	float AttackWalkSpeed;

	// Perhaps not component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWeaponComponent* WeaponComponent;

	ABottomDwellerCharacter();

	void RecalculateDamage();

	UFUNCTION(BlueprintCallable, BlueprintSetter)
	void SetInventoryComponent(UInventoryComponent* NewInventoryComponent) {
		InventoryComponent = NewInventoryComponent;
	}

	UFUNCTION(BlueprintPure, BlueprintCallable, BlueprintGetter)
	UInteractionComponent* GetInteractionComponent() const {
		return InteractionComponent;
	}

	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintPure, BlueprintCallable, BlueprintGetter)
	virtual UCharacterMovementComponent* GetPawnMovementComponent_Implementation() const override {
		return GetCharacterMovement();
	}

	virtual void OnActorLoaded_Implementation() override;
	virtual void BeginAttack_Implementation() override;
	virtual void EndAttack_Implementation() override;
	virtual void EnableWeaponTracing_Implementation() override;
	virtual void DisableWeaponTracing_Implementation() override;

protected:
	UFUNCTION(BlueprintCallable)
	void Move(float ForwardValue, float RightValue);

	virtual void BeginPlay() override;

private:
	void InitActorComponents();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> PointLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInteractionComponent> InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipmentComponent> EquipmentComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
};
