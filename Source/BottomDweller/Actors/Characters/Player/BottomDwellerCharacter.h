// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/BaseCharacter.h"
#include "BottomDweller/Actors/Characters/MeleeAttacker.h"
#include "BottomDweller/Actors/Components/SupportInterfaces/InventorySupport.h"
#include "BottomDwellerCharacter.generated.h"

class UInteractionComponent;
class UPointLightComponent;
class UCameraComponent;
class UInventoryComponent;

UCLASS(config=Game)
class ABottomDwellerCharacter : public ABaseCharacter, public IMeleeAttacker, public IInventorySupport
{
	GENERATED_BODY()

	void InitActorComponents();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> PointLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInteractionComponent> InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), SaveGame)
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

protected:
	UFUNCTION(BlueprintCallable)
	void Move(float ForwardValue, float RightValue);

	virtual void BeginPlay() override;

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
	void SetInventoryComponent(UInventoryComponent* NewInventoryComponent)
	{
		InventoryComponent = NewInventoryComponent;
	}

	UFUNCTION(BlueprintPure, BlueprintCallable, BlueprintGetter)
	UInteractionComponent* GetInteractionComponent() const
	{
		return InteractionComponent;
	}

	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	
	UFUNCTION(BlueprintPure, BlueprintCallable, BlueprintGetter)
	virtual UInventoryComponent* GetInventoryComponent_Implementation() override
	{
		return InventoryComponent;
	}
	
	virtual void OnActorLoaded_Implementation() override;
	virtual void BeginAttack_Implementation() override;
	virtual void EndAttack_Implementation() override;
	virtual void EnableWeaponTracing_Implementation() override;
	virtual void DisableWeaponTracing_Implementation() override;
};
