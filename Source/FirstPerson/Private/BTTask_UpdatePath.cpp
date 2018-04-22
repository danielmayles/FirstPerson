#include "BTTask_UpdatePath.h"
#include "Classes/AIController.h"

EBTNodeResult::Type UBTTask_UpdatePath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIController->GetPawn();
	UBlackboardComponent* BlackBoardComponent = AIController->GetBlackboardComponent();

	if (BlackBoardComponent != nullptr)
	{
		if (CurrentPath != nullptr && CurrentPath->PathPoints.Num() > 1)
		{
			float DistanceFromPathPoint = (CurrentPath->PathPoints[CurrentPathPointIndex] - ControlledPawn->GetActorLocation()).Size();
			if (DistanceFromPathPoint <= AcceptableDistanceFromPathPoint)
			{
				CurrentPathPointIndex++;
				if (IsAtEndOfPath())
				{
					CurrentPath = nullptr;
					return EBTNodeResult::Succeeded;
				}
			}

			BlackBoardComponent->SetValueAsVector(CurrentTargetLocationKey.SelectedKeyName, CurrentPath->PathPoints[CurrentPathPointIndex]);
		}
		else
		{
			AActor* Target = Cast<AActor>(BlackBoardComponent->GetValueAsObject(CurrentTargetKey.SelectedKeyName));
			if (Target != nullptr)
			{
				CurrentPath = UNavigationSystem::FindPathToLocationSynchronously(GetWorld(), ControlledPawn->GetActorLocation(), Target->GetActorLocation());
				CurrentPathPointIndex = 0;
			}
		}
	}

	return EBTNodeResult::Failed;
}


bool UBTTask_UpdatePath::IsAtEndOfPath()
{
	if (CurrentPathPointIndex >= CurrentPath->PathPoints.Num())
	{
		return true;
	}
	return false;
}
