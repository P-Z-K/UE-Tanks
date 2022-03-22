// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tanks/Audio/AudioManager.h"
#include "TanksGameMode.generated.h"

class ATanksPlayerController;
class ATank;
class UStartGameWidgetBase;
/**
 * 
 */
UCLASS()
class TANKS_API ATanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	ATanksGameMode();
	virtual void BeginPlay() override;
	
	void HandlePreStart();
	void HandleGameEnd();
	void PrepareLevel();
	void DisplayCountdown();
	
	void EnablePlayer();
	void DisablePlayer();

	UFUNCTION()
	void HandleGameOver();

	UFUNCTION()
	void HandleWin();

	UFUNCTION()
	void HandleGameStart();

	UFUNCTION()
	void PlayCountdownSound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartDelay = 10.f;
	
	UPROPERTY()
	UStartGameWidgetBase* StartGameWidgetInstance = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAudioManager> AudioManager;

	UPROPERTY()
	UAudioManager* AudioManagerInstance = nullptr;
	
	UPROPERTY()
	ATanksPlayerController* PlayerController = nullptr;
	
	UPROPERTY()
	ATank* Player = nullptr;
	
	UPROPERTY()
	UUserWidget* GameOverWidgetInstance = nullptr;
	
	UPROPERTY()
	UUserWidget* WinWidgetInstance = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameOverWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WinWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UStartGameWidgetBase> CountdownWidget;
};
