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

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
protected:
	/** Called for movement input */
	UFUNCTION(BlueprintCallable)
	void Move(float ForwardValue, float RightValue);
	
public:

	UPROPERTY(EditAnywhere)
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere)
	FRotator RotationRate;
	
	UPROPERTY(EditAnywhere)
	float AttackWalkSpeed;

	UPROPERTY(EditAnywhere)
	FRotator AttackRotationRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeaponComponent;
	
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
