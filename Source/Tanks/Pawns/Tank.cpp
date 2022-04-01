// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
}

void ATank::SetStartPosition(const FVector& Position, const FRotator& Rotation)
{
	this->SetActorLocation(Position);
	this->SetActorRotation(Rotation);
	TurretMesh->SetWorldRotation(Rotation);
}

ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring arm component");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera component");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
	PlayerInputComponent->BindAxis("Turn", this, &ATank::RotateBase);
	PlayerInputComponent->BindAction("Fire", IE_Pressed,this, &ATank::Fire);
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	RotateTurret(GetMouseCursorImpactPoint());
}

void ATank::OnDie()
{
	Super::OnDie();
	OnTankDie.Broadcast();
}

FVector ATank::GetMouseCursorImpactPoint() const
{
	FHitResult Result;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, OUT Result);
	return Result.ImpactPoint;
}

void ATank::Move(float Value)
{
	float XValue = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * BaseMovementSpeed;
	this->AddActorLocalOffset(FVector(XValue, 0.f, 0.f), true);
}

void ATank::RotateBase(float Value)
{
	float YawValue = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * BaseRotationSpeed;
	this->AddActorLocalRotation(FRotator(0.f, YawValue, 0.f), true);
}
