// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

class ATurret;

DECLARE_EVENT_OneParam(ATurret, FOnTurretDie, ATurret*)

UCLASS()
class TANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootingDistance = 0.f;

	FOnTurretDie OnTurretDie;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnDie() override;

private:
	UPROPERTY()
	class ATanksPlayerController* PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool bEnableDebuggingShootingDistance = false;


	void WatchOver();
	void Debug_ShootingDistance();
	void Debug_Firing();
	void Debug();
	bool IsInFireRange();
	void TryFire();
	void ToggleTimer(bool bShouldBeActivated);

	FTimerHandle FireRateTimerHandle;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float FireRate = 2.f;

	
	
};