// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHit, FHitResult, HitResult)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOTTOMDWELLER_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

	TArray<FName> Sockets;
	TMap<FName, FVector> SocketLocations;
	TArray<FHitResult> HitArray;
	
	UPROPERTY(VisibleAnywhere)	
	bool bCanTrace;

	UPROPERTY(EditAnywhere)
	bool bDrawDebug;

	void UpdateLastKnowSocketLocations();
	void AddToHitArray(TArray<FHitResult> HitArrayToAdd);

public:
	// Sets default values for this component's properties
	UWeaponComponent();

	UPROPERTY(BlueprintAssignable)
	FOnHit OnHit;

	UFUNCTION()
	void SetCanTrace(bool CanTrace);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void SetSkeletalMesh(USkeletalMesh* NewMesh, bool bReinitPose = false) override;

	
};
