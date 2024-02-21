// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WeaponComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOTTOMDWELLER_API UWeaponComponent final : public USkeletalMeshComponent {
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHit, FHitResult, HitResult)

	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

	UPROPERTY(BlueprintAssignable)
	FOnHit OnHit;

	UFUNCTION()
	void SetCanTrace(bool CanTrace);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetSkeletalMesh(USkeletalMesh* NewMesh, bool bReinitPose = false) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	TArray<FName> Sockets;
	TMap<FName, FVector> SocketLocations;
	TArray<FHitResult> HitArray;

	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY(VisibleAnywhere)
	bool bCanTrace;

	UPROPERTY(EditAnywhere)
	bool bDrawDebug;

	void UpdateLastKnowSocketLocations();
	void AddToHitArray(TArray<FHitResult> HitArrayToAdd);
};
