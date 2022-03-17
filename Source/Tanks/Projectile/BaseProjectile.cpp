// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	Model = CreateDefaultSubobject<UStaticMeshComponent>("Model");
	RootComponent = Model;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>("TrailParticles");
	TrailParticles->SetupAttachment(RootComponent);
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	Model->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
	Model->IgnoreActorWhenMoving(GetInstigator(), true);

	GetWorldTimerManager().SetTimer(AutoDestructionTimerHandle, this, &ABaseProjectile::DestroySelf,
	                                AutoDestructionAfterInSeconds);
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void ABaseProjectile::DestroySelf()
{
	Destroy();
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            FVector NormalImpluse, const FHitResult& Hit)
{
	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetOwner()->GetInstigatorController(), this,
	                              UDamageType::StaticClass());
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShake);
	if (HitParticle)
	{
		ParticleScale = FVector(0.7f);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation(), ParticleScale, 
		true, EPSCPoolMethod::AutoRelease);
	}
	this->Destroy();
}
