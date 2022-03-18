// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tanks/Core/HealthComponent.h"
#include "Tanks/Projectile/BaseProjectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule Component");
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Projectile Spawn Point");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnHealthWentBelowZero.AddUObject(this, &ABasePawn::OnDie);
}

void ABasePawn::OnDie()
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShake);
}

void ABasePawn::RotateTurret(const FVector& To)
{
	FVector TargetDirection = To - TurretMesh->GetComponentLocation();
	TargetDirection.Normalize();
	FRotator RotationToTarget(0.f, TargetDirection.Rotation().Yaw, 0.f);
	auto InterpolatedRotation = FMath::RInterpConstantTo(TurretMesh->GetComponentRotation(),
	                                                     RotationToTarget,
	                                                     UGameplayStatics::GetWorldDeltaSeconds(this),
	                                                     TurretRotationSpeed);
	TurretMesh->SetWorldRotation(InterpolatedRotation);
}

void ABasePawn::Fire()
{
	auto x = GetWorld()->SpawnActorDeferred<ABaseProjectile>(Projectile, GetTransform(), this, this);
	x->SetActorLocationAndRotation(ProjectileSpawnPoint->GetComponentLocation(),
	                               ProjectileSpawnPoint->GetComponentRotation());
	x->FinishSpawning(GetTransform());
}
