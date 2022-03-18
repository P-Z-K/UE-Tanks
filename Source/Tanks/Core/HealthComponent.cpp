// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::ApplyDamage);
}

void UHealthComponent::ApplyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                   AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	if (Health >= 0.f)
	{
		Health -= Damage;

		if (Health <= 0.f)
			OnHealthWentBelowZero.Broadcast();
	}
	UE_LOG(LogTemp, Warning, TEXT("Object %s has: %f HP"), *GetOwner()->GetName(), Health);
}
