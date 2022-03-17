// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EnemiesSubsystem.generated.h"

class ATurret;
/**
 * 
 */
DECLARE_EVENT(UEnemiesSubsystem, FOnAllEnemiesDied)

UCLASS()
class TANKS_API UEnemiesSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<ATurret*> Enemies;

public:
	void RegisterEnemy(ATurret* Enemy);
	int GetEnemiesCount() const;

	FOnAllEnemiesDied OnAllEnemiesDied;

	UFUNCTION()
	void OnEnemyDied(ATurret* DiedEnemy);
};
