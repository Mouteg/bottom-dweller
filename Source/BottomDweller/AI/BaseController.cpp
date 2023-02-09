// All rights reserved by Aboba Inc.


#include "BaseController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ABaseController::BeginPlay()
{
	Super::BeginPlay();
	
	if (AIBehaviourTree)
	{
		RunBehaviorTree(AIBehaviourTree);
	}
	
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (BlackboardComponent && PlayerPawn)
	{
		// BlackboardComponent->SetValueAsVector(TEXT("CurrentPlayerLocation"), PlayerPawn->GetActorLocation());
		// BlackboardComponent->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}
