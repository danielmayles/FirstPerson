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

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Die();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IDamageable Interface")
	void ApplyDamage(int DamageAmount);

	UFUNCTION(BlueprintCallable)
	bool IsOnFloor();

private:
	int Health;
	bool IsAlive;
};
