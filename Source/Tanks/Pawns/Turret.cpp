// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "DrawDebugHelpers.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Tanks/Core/HealthComponent.h"
#include "Tanks/Core/TanksPlayerController.h"
#include "Tanks/Enemy/EnemiesSubsystem.h"



void ATurret::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ATanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	UEnemiesSubsystem* System = GetWorld()->GetSubsystem<UEnemiesSubsystem>();
	if (System)
	{
		System->RegisterEnemy(this);
	}
}

void ATurret::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Debug();
	WatchOver();
}

void ATurret::OnDie()
{
	Super::OnDie();
	OnTurretDie.Broadcast(this);
}

void ATurret::Enable()
{
	this->SetActorTickEnabled(true);
	this->SetActorHiddenInGame(false);
	this->SetActorEnableCollision(true);
}

void ATurret::Disable()
{
	this->SetActorTickEnabled(false);
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
}

void ATurret::WatchOver()
{
	if (IsInFireRange() && !PlayerController->GetPawn()->IsHidden())
	{
		RotateTurret(PlayerController->GetPawn()->GetActorLocation());
		TryFire();
	}
}

void ATurret::Debug_ShootingDistance()
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), ShootingDistance, 15, DebugUtilColor->Blue);
}

void ATurret::Debug_Firing()
{
	DrawDebugSphere(GetWorld(),
	                ProjectileSpawnPoint->GetComponentLocation(),
	                10.f,
	                15,
	                DebugUtilColor->Red,
	                false,
	                1.5f);
}

void ATurret::Debug()
{
	if (bEnableDebuggingShootingDistance)
	{
		Debug_ShootingDistance();
	}
}

bool ATurret::IsInFireRange()
{
	float Distance = FVector::Dist(GetActorLocation(), PlayerController->GetPawn()->GetActorLocation());
	if (Distance <= ShootingDistance)
	{
		return true;
	}
	return false;
}

void ATurret::TryFire()
{
	if (!IsInFireRange() || bIsReloading || !HasRequiredAngleToShoot())
	{
		return;
	}
	
	if (bEnableDebuggingShootingDistance)
		Debug_Firing();
	
	Fire();
	bIsReloading = true;
	GetWorldTimerManager().ClearTimer(FireRateTimerHandle);
	Delegate = FTimerDelegate::CreateUObject(this, &ATurret::SetIsReloading, false);
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, Delegate, FireRate, false);
}

bool ATurret::HasRequiredAngleToShoot()
{
	auto TargetDirectionToPlayer = PlayerController->GetPawn()->GetActorLocation() - GetActorLocation();
	auto n2 = TargetDirectionToPlayer;
	n2.Normalize();

	float Cosinus = TurretMesh->GetForwardVector().CosineAngle2D(n2);
	float Angle = FMath::RadiansToDegrees(FMath::Acos(Cosinus));

	return Angle <= StartAngleToShoot;
}


void ATurret::RestartHealth() const
{
	if (HealthComponent)
	{
		HealthComponent->RestartHealth();
	}
}
