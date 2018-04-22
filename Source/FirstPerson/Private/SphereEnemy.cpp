#include "SphereEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

ASphereEnemy::ASphereEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Enemy Collider"));
	Collider->SetSimulatePhysics(true);
	Collider->OnComponentHit.AddDynamic(this, &ASphereEnemy::OnHit);
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	Mesh->SetupAttachment(Collider);

	SetHealth(10);
}


void ASphereEnemy::Die()
{
}

void ASphereEnemy::ApplyDamage_Implementation(int DamageAmount)
{
	Super::ApplyDamage_Implementation(DamageAmount);
	SetActorScale3D(GetActorScale3D() * 0.5f);
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

void ASphereEnemy::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}

		if (OtherActor->GetClass() != GetClass() && OtherActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
		{
			IDamageable::Execute_ApplyDamage(OtherActor, 10);
		}
	}
}

