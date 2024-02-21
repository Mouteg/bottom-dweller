// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Maps/Activatable.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UENUM(BlueprintType)
enum class EDoorOpenType : uint8 {
	Rotation,
	Slide
};

UCLASS()
class BOTTOMDWELLER_API ADoor : public AActor, public IActivatable {
	GENERATED_BODY()

public:
	ADoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere)
	EDoorOpenType OpenType;

	UPROPERTY(EditAnywhere)
	bool bIsOpened;

	UPROPERTY(EditAnywhere)
	bool bAutoClose;

	UPROPERTY(EditAnywhere, meta=(EditConditionHides, EditCondition="bAutoClose"))
	float Delay;

	UPROPERTY(EditAnywhere, meta=(EditConditionHides, EditCondition="OpenType == EDoorOpenType::Slide"))
	FVector OpenOffset;

	UPROPERTY(EditAnywhere, meta=(EditConditionHides, EditCondition="OpenType == EDoorOpenType::Rotation"))
	FRotator OpenAngle;

	virtual void Activate_Implementation() override;

	UFUNCTION()
	void ChangeDoorState();

protected:
	virtual void BeginPlay() override;

private:
	bool IsTimerLocked;

	void AutoClose();
};
