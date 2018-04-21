#include "Enemy.h"

AEnemy::AEnemy():
	Health(100)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemy::ApplyDamage_Implementation(int DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		Die();
	}
	OnDamaged();
}

void AEnemy::Die()
{
	Destroy();
}

void AEnemy::SetHealth(int NewHealthValue)
{
	Health = NewHealthValue;

}

bool AEnemy::IsOnFloor()
{
	FHitResult HitData;
	FCollisionQueryParams CollisionParams;
	FVector Origin;
	FVector BoundsExtent;
	GetActorBounds(true, Origin, BoundsExtent);

	const FVector Start = GetActorLocation() - BoundsExtent.Z;
	const FVector End = Start + FVector(0, 0, -1);

	if (GetWorld()->LineTraceSingleByChannel(HitData, Start, End, ECC_Visibility, CollisionParams))
	{
		float HitDistance = FVector::Dist(Start, HitData.ImpactPoint);
		if (HitDistance <= 0.0f)
		{
			return true;
		}
	}

	return false;
}

void AEnemy::OnDamaged()
{
}

