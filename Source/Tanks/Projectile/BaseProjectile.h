// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BaseProjectile.generated.h"

UCLASS()
class TANKS_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

protected:
	ABaseProjectile();
	virtual void BeginPlay() override;

	FTimerHandle AutoDestructionTimerHandle;
	void DestroySelf();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpluse,
			   const FHitResult& Hit);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Model = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* HitSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* LaunchSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCameraShakeBase> HitCameraShake = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UParticleSystem* HitParticle = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	FVector ParticleScale = FVector(1.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UParticleSystemComponent* TrailParticles = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float Damage = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float AutoDestructionAfterInSeconds = 0.f;
};
