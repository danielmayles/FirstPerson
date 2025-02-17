// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NPCPawn.h"
#include "SphereEnemy.generated.h"

UCLASS()
class FIRSTPERSON_API ASphereEnemy : public ANPCPawn
{
	GENERATED_BODY()

public:
	ASphereEnemy();
	virtual void Die() override;
	virtual void ApplyDamage_Implementation(int DamageAmount) override;

	UFUNCTION(BlueprintCallable)
	virtual void MoveTowardsPosition(FVector TargetPosition) override;

	UFUNCTION(BlueprintCallable)
	void Jump(FVector JumpDirection, float JumpForce);
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Options")
	float DamagePerAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Options")
	float ScaleModifierPerHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Options")
	float TorqueModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Options")
	float MinVelocityToDoDamage;

private:
	void TemporarilyDisableAttacking(float AmountTimeToDisable);
	void DisableAttacking();
	void EnableAttacking();

	bool AbleToDoDamage;
};
