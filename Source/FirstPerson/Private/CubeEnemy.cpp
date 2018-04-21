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
	if (IsOnFloor())
	{
		FVector TargetDirection = (TargetPosition - GetActorLocation()).GetSafeNormal();
		FVector DirectionalTorque = FVector::CrossProduct(FVector(0, 0, 1), TargetDirection);
		//DirectionalTorque *= 1000;

		DirectionalTorque *= 1500000 * CubeCollider->GetMass();
		//FRotator Rotation = FRotator(DirectionalTorque.Y, DirectionalTorque.Z, DirectionalTorque.X);
		//Rotation *= 10.0f;

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Rotation.ToString());

		CubeCollider->AddTorque(DirectionalTorque);
		//CubeCollider->AddWorldRotation(Rotation, true);
		//CubeCollider->AddTorqueInDegrees(DirectionalTorque, "None", false);
		//CubeCollider->AddImpulse(TargetDirection * 1000, "None", true);
	}
}

void ACubeEnemy::Jump(FVector JumpDirection, float JumpForce)
{
	if (IsOnFloor())
	{
		JumpDirection.Z = 1;
		CubeCollider->AddImpulse(JumpDirection * JumpForce, "None",  true);
	}
}

