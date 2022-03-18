// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UHealthComponent;
class UCapsuleComponent;

UCLASS()
class TANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

protected:
	ABasePawn();
	virtual void BeginPlay() override;
	
	void RotateTurret(const FVector& To);
	void Fire();

	UFUNCTION()
	virtual void OnDie();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurretRotationSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TurretMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ProjectileSpawnPoint = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHealthComponent* HealthComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* DeathParticles = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* DeathSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCameraShakeBase> DeathCameraShake = nullptr;
};
