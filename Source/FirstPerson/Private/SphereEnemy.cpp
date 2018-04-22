#include "SphereEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FirstPersonCharacter.h"

ASphereEnemy::ASphereEnemy() :
	ScaleModifierPerHit(0.5f),
	TorqueModifier(10000),
	DamagePerAttack(20),
	AbleToDoDamage(true)
{
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Enemy Collider"));
	Collider->SetSimulatePhysics(true);
	Collider->OnComponentHit.AddDynamic(this, &ASphereEnemy::OnHit);
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	Mesh->SetupAttachment(Collider);

	SetHealth(3);
}

void ASphereEnemy::Die()
{
	Destroy();
}

void ASphereEnemy::ApplyDamage_Implementation(int DamageAmount)
{
	Super::ApplyDamage_Implementation(DamageAmount);
	SetActorScale3D(GetActorScale3D() * ScaleModifierPerHit);
}

void ASphereEnemy::MoveTowardsPosition(FVector TargetPosition)
{
	FVector TargetDirection = (TargetPosition - GetActorLocation()).GetSafeNormal();
	FVector TorqueDirection = FVector::CrossProduct(FVector(0, 0, 1), TargetDirection);
	TorqueDirection *= (TorqueModifier * GetWorld()->GetDeltaSeconds());
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
		if (MinVelocityToDoDamage < (GetVelocity()).Size() && AbleToDoDamage)
		{
			if (OtherActor->GetClass() != GetClass() && OtherActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
			{
				IDamageable::Execute_ApplyDamage(OtherActor, DamagePerAttack);
				TemporarilyDisableAttacking(1.0f);			
			}
		}
	}
}

void ASphereEnemy::TemporarilyDisableAttacking(float AmountTimeToDisable)
{
	DisableAttacking();
	FTimerHandle DamageDisableTimer;
	GetWorld()->GetTimerManager().SetTimer(DamageDisableTimer, this, &ASphereEnemy::EnableAttacking, 1.0f);
}

void ASphereEnemy::DisableAttacking()
{
	AbleToDoDamage = false;
}

void ASphereEnemy::EnableAttacking()
{
	AbleToDoDamage = true;
}

