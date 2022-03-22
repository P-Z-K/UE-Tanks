// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

UAudioManager::UAudioManager()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio Component");
}

UWorld* UAudioManager::GetWorld() const
{
	return GetOuter()->GetWorld();
}

void UAudioManager::PlayBackgroundMusic()
{
	AudioComponent->SetSound(BackgroundMusic);
	AudioComponent->FadeIn(BackgroundMusicFadeInDuration);
}

void UAudioManager::StopBackgroundMusic()
{
	AudioComponent->FadeOut(BackgroundMusicFadeOutDuration, 0.f);
}

void UAudioManager::PlayClockSound()
{
	if (CountdownSound)
	{
		UGameplayStatics::PlaySound2D(this, CountdownSound);
	}
}

void UAudioManager::PlayCountdownEndSound()
{
	if (CountdownEndSound)
	{
		UGameplayStatics::PlaySound2D(this, CountdownEndSound);
	}
}


