// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

ACubeEnemy::ACubeEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CubeCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Enemy Collider"));
	CubeCollider->SetSimulatePhysics(true);
	//CubeCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	RootComponent = CubeCollider;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	CubeMesh->SetupAttachment(CubeCollider);
	
}

void ACubeEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACubeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACubeEnemy::MoveTowardsPosition(FVector TargetPosition)
{
	FVector TargetDirection = (TargetPosition - GetActorLocation()).GetSafeNormal();
	FVector JumpVector = TargetDirection;
	JumpVector.Z = 1;
	Jump(JumpVector, 100.0f);
}

void ACubeEnemy::Jump(FVector JumpDirection, float JumpForce)
{
	if (IsOnFloor())
	{
		CubeCollider->AddImpulse(JumpDirection * JumpForce, "None",  true);
	}
}

