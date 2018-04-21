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

}

bool AEnemy::IsFalling()
{
	if (GetVelocity().Z < 0)
	{
		return true;
	}

	return false;
}

