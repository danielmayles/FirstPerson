#include "Enemy.h"

AEnemy::AEnemy():
	Health(100)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::ApplyDamage_Implementation(int DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		Die();
	}
}

void AEnemy::Die()
{
	Destroy();
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
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(HitDistance));
		if (HitDistance <= 0.0f)
		{
			return true;
		}
	}

	return false;
}

