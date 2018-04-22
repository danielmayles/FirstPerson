// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Navigation/NavigationData.h"
#include "AI/Navigation/NavigationPath.h"
#include "AI/Navigation/NavigationSystem.h"
#include "BTTask_UpdatePath.generated.h"

UCLASS()
class FIRSTPERSON_API UBTTask_UpdatePath : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BlackboardKeys)
	FBlackboardKeySelector CurrentTargetLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BlackboardKeys)
	FBlackboardKeySelector CurrentTargetKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AcceptableDistanceFromPathPoint;

	UNavigationPath* CurrentPath;

private: 
	bool IsAtEndOfPath();
	int CurrentPathPointIndex;
};
