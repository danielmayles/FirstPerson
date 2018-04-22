#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Damageable.h"
#include "Enemy.generated.h"

UCLASS()
class FIRSTPERSON_API AEnemy : public APawn, public IDamageable
{
	GENERATED_BODY()

public:	
	AEnemy();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IDamageable Interface")
	void ApplyDamage(int DamageAmount);
	virtual void ApplyDamage_Implementation(int DamageAmount);

	UFUNCTION(BlueprintCallable)
	virtual void MoveTowardsPosition(FVector TargetPosition);

	UFUNCTION(BlueprintCallable)
	void SetHealth(int NewHealthValue);

	UFUNCTION(BlueprintCallable)
	bool IsOnFloor();

	UFUNCTION(BlueprintCallable)
	virtual void Die();

private:
	int Health;
	bool IsAlive;
};
