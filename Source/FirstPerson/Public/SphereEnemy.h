// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "SphereEnemy.generated.h"

UCLASS()
class FIRSTPERSON_API ASphereEnemy : public AEnemy
{
	GENERATED_BODY()

public:
	ASphereEnemy();

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* Collider;

	UFUNCTION(BlueprintCallable)
	void MoveTowardsPosition(FVector TargetPosition);	 

	UFUNCTION(BlueprintCallable)
	void Jump(FVector JumpDirection, float JumpForce);
};
