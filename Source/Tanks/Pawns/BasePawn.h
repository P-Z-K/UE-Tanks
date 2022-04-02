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

public:
	FORCEINLINE UHealthComponent* GetHealthComponent() const {return HealthComponent;} 

protected:
	ABasePawn();
	virtual void BeginPlay() override;
	
	void RotateTurret(const FVector& To);
	void Fire();

	UFUNCTION()
	virtual void OnDie();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurretRotationSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TurretMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* ProjectileSpawnPoint = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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
