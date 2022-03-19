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
	virtual void OnDie() override;
	FOnTurretDie OnTurretDie;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	void WatchOver();
	void Debug_ShootingDistance();
	void Debug_Firing();
	void Debug();
	bool IsInFireRange();
	void TryFire();
	bool HasRequiredAngleToShoot();

	UFUNCTION()
	void SetIsReloading(bool Value);

	FTimerHandle FireRateTimerHandle;
	FTimerDelegate Delegate;

	bool bIsReloading = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float FireRate = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta=(AllowPrivateAccess, ToolTip=
			"Start angle between turret's forward vector and the player position in which the turret starts shooting"
		))
	float StartAngleToShoot = 6.f;

	UPROPERTY()
	class ATanksPlayerController* PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool bEnableDebuggingShootingDistance = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootingDistance = 0.f;
};
