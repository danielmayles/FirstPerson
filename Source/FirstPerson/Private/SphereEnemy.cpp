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

	SetHealth(10);
}


void ASphereEnemy::Die()
{
}

void ASphereEnemy::OnDamaged()
{
	SetActorScale3D(GetActorScale3D() * 0.90f);
}

void ASphereEnemy::MoveTowardsPosition(FVector TargetPosition)
{
	FVector TargetDirection = (TargetPosition - GetActorLocation()).GetSafeNormal();
	FVector TorqueDirection = FVector::CrossProduct(FVector(0, 0, 1), TargetDirection);
	TorqueDirection *= (10000 * GetWorld()->GetDeltaSeconds());
	Collider->AddTorqueInRadians(TorqueDirection, "None", true);
}

void ASphereEnemy::Jump(FVector JumpDirection, float JumpForce)
{
	if (IsOnFloor())
	{
		JumpDirection.Z = 1;
		Collider->AddImpulse(JumpDirection * JumpForce, "None",  true);
	}
}

