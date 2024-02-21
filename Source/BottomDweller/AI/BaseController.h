// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseController.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API ABaseController : public AAIController {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* AIBehaviourTree = nullptr;

	UPROPERTY(VisibleAnywhere)
	APawn* PlayerPawn = nullptr;
};
