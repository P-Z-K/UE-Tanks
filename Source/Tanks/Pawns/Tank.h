// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;

DECLARE_EVENT(ATank, FOnTankDie)

/**
 * 
 */
UCLASS()
class TANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	FOnTankDie OnTankDie;

	void SetStartPosition(const FVector& Position, const FRotator& Rotation);


protected:
	ATank();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	FVector GetMouseCursorImpactPoint() const;
	virtual void OnDie() override;
	void Move(float Value);
	void RotateBase(float Value);

	bool bHasDestroyed = false;

	UPROPERTY()
	APlayerController* PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseMovementSpeed = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseRotationSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent = nullptr;
	
	
};
