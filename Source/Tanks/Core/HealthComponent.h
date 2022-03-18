// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_EVENT(UHealthComponent, FOnHealthWentBelowZero)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnHealthWentBelowZero OnHealthWentBelowZero;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ApplyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator,
					 AActor* DamageCauser);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float Health = 0.f;
};
