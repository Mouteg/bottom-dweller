// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/BaseCharacter.h"
#include "BottomDweller/Actors/Characters/MeleeAttacker.h"
#include "BottomDwellerCharacter.generated.h"

UCLASS(config=Game)
class ABottomDwellerCharacter : public ABaseCharacter, public IMeleeAttacker
{
	GENERATED_BODY()
	
	void InitActorComponents();

	UPROPERTY(EditAnywhere)
	float Sensitivity;

	UPROPERTY(EditAnywhere)
	float AttackSensitivityMultiplier;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent* PointLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), SaveGame)
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
protected:
	UFUNCTION(BlueprintCallable)
	void Move(float ForwardValue, float RightValue);
	
public:

	UPROPERTY(EditAnywhere)
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere)
	float AttackWalkSpeed;

	// Perhaps not component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWeaponComponent* WeaponComponent;
	
	ABottomDwellerCharacter();
	
	UFUNCTION(BlueprintCallable, BlueprintSetter)
	void SetInventoryComponent(UInventoryComponent* NewInventoryComponent)
	{
		InventoryComponent = NewInventoryComponent;
	}
	
	UFUNCTION(BlueprintCallable, BlueprintSetter)
	void SetInteractionComponent(UInteractionComponent* NewInteractionComponent)
	{
		InteractionComponent = NewInteractionComponent;
	}
	

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

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetSensitivity();
	
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	virtual void OnActorLoaded_Implementation() override;
	virtual void BeginAttack_Implementation() override;
	virtual void EndAttack_Implementation() override;
	virtual void EnableWeaponTracing_Implementation() override;
	virtual void DisableWeaponTracing_Implementation() override;
};
