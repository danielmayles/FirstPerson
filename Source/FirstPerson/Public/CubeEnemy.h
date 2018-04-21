// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "CubeEnemy.generated.h"

UCLASS()
class FIRSTPERSON_API ACubeEnemy : public AEnemy
{
	GENERATED_BODY()

public:
	ACubeEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* CubeCollider;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void MoveTowardsPosition(FVector TargetPosition);	 

	UFUNCTION(BlueprintCallable)
	void Jump(FVector JumpDirection, float JumpForce);
};
