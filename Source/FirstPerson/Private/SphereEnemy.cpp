#include "SphereEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

ASphereEnemy::ASphereEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Enemy Collider"));
	Collider->SetSimulatePhysics(true);
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	Mesh->SetupAttachment(Collider);
	
}

void ASphereEnemy::MoveTowardsPosition(FVector TargetPosition)
{
	if (IsOnFloor())
	{
		FVector TargetDirection = (TargetPosition - GetActorLocation()).GetSafeNormal();
		FVector DirectionalTorque = FVector::CrossProduct(FVector(0, 0, 1), TargetDirection);

		DirectionalTorque *= (1000000 * GetWorld()->GetDeltaSeconds());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Rotation.ToString());

		Collider->AddTorqueInDegrees(DirectionalTorque, "None", true);
	}
}

void ASphereEnemy::Jump(FVector JumpDirection, float JumpForce)
{
	if (IsOnFloor())
	{
		JumpDirection.Z = 1;
		Collider->AddImpulse(JumpDirection * JumpForce, "None",  true);
	}
}

