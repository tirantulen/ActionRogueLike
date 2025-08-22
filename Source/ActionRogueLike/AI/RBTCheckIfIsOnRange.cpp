// Fill out your copyright notice in the Description page of Project Settings.


#include "RBTCheckIfIsOnRange.h"
#include "AIController.h"

#include "BehaviorTree/BlackboardComponent.h"

void URBTCheckIfIsOnRange::TickNode(UBehaviorTreeComponent& Comp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(Comp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComp = Comp.GetBlackboardComponent();
	if (ensure(BlackboardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* MyController = Comp.GetAIOwner();
			if (ensure(MyController))
			{
				APawn* AIPawn = MyController->GetPawn();
				if (ensure(AIPawn))
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bWithinRange = DistanceTo < 1000.0f;

					bool bIsVisibile = MyController->LineOfSightTo(TargetActor);

					BlackboardComp->SetValueAsBool("bIsOnRange", (bWithinRange && bIsVisibile));
				}
			}
		}
	}
}
