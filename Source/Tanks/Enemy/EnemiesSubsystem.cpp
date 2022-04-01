// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesSubsystem.h"

#include "Tanks/Pawns/Turret.h"


void UEnemiesSubsystem::RegisterEnemy(ATurret* Enemy)
{
	Enemy->OnTurretDie.AddUObject(this, &UEnemiesSubsystem::OnEnemyDied);
	Enemies.Add(Enemy);
	++EnemiesCount;
}

int UEnemiesSubsystem::GetEnemiesCount() const
{
	return Enemies.Num();
}

void UEnemiesSubsystem::ReviveEnemies()
{
	EnemiesCount = Enemies.Num();
	for (const auto& e : Enemies)
	{
		e->OnTurretDie.AddUObject(this, &UEnemiesSubsystem::OnEnemyDied);
		e->Enable();
		e->RestartHealth();
	}
}

void UEnemiesSubsystem::OnEnemyDied(ATurret* DiedEnemy)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy %s has died!"), *DiedEnemy->GetName());

	--EnemiesCount;
	DiedEnemy->OnTurretDie.Clear();
	DiedEnemy->Disable();
	
	if (EnemiesCount <= 0)
	{
		OnAllEnemiesDied.Broadcast();
	}
}
