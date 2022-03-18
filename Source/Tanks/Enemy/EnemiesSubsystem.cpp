// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesSubsystem.h"

#include "Tanks/Pawns/Turret.h"


void UEnemiesSubsystem::RegisterEnemy(ATurret* Enemy)
{
	Enemy->OnTurretDie.AddUObject(this, &UEnemiesSubsystem::OnEnemyDied);
	Enemies.Add(Enemy);
}

int UEnemiesSubsystem::GetEnemiesCount() const
{
	return Enemies.Num();
}

void UEnemiesSubsystem::OnEnemyDied(ATurret* DiedEnemy)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy %s has died!"), *DiedEnemy->GetName());

	Enemies.Remove(DiedEnemy);
	DiedEnemy->OnTurretDie.Clear();
	DiedEnemy->Destroy();
	if (Enemies.Num() <= 0)
	{
		OnAllEnemiesDied.Broadcast();
	}
}
