// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "DrawDebugHelpers.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Tanks/Core/TanksPlayerController.h"
#include "Tanks/Enemy/EnemiesSubsystem.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ATanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	UEnemiesSubsystem* system = GetWorld()->GetSubsystem<UEnemiesSubsystem>();
	if (system)
	{
		system->RegisterEnemy(this);
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

void ATurret::WatchOver()
{
	if (IsInFireRange() && !PlayerController->GetPawn()->IsHidden())
	{
		RotateTurret(PlayerController->GetPawn()->GetActorLocation());
		ToggleTimer(true);
		return;
	}

	ToggleTimer(false);
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
	if (IsInFireRange())
	{
		UE_LOG(LogTemp, Warning, TEXT("Firing!"));
		if (bEnableDebuggingShootingDistance)
			Debug_Firing();
		Fire();
	}
}

void ATurret::ToggleTimer(bool bShouldBeActivated)
{
	if (bShouldBeActivated)
	{
		if (!FireRateTimerHandle.IsValid())
		{
			GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::TryFire, FireRate, true);
		}
		return;
	}

	if (GetWorldTimerManager().IsTimerActive(FireRateTimerHandle))
	{
		UE_LOG(LogTemp, Warning, TEXT("Pausing timer!"));
		GetWorldTimerManager().ClearTimer(FireRateTimerHandle);
	}
}
