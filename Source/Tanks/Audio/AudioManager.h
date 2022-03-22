// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AudioManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TANKS_API UAudioManager : public UObject
{
	GENERATED_BODY()

public:
	void PlayBackgroundMusic();
	void StopBackgroundMusic();

	void PlayClockSound();
	void PlayCountdownEndSound();

protected:
	UAudioManager();
	virtual UWorld* GetWorld() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BackgroundMusicFadeInDuration = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BackgroundMusicFadeOutDuration = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* CountdownEndSound = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* AudioComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* CountdownSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* BackgroundMusic = nullptr;
};
