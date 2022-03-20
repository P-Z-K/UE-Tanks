// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
	virtual void BeginPlay() override;
	
	void HandlePreStart();
	void PrepareLevel();
	void DisplayCountdown();
	void EnablePlayer();
	void HandleGameOver();
	void HandleWin();
	void DisablePlayer();

	UFUNCTION()
	void HandleGameStart();

	UFUNCTION()
	void PlayCountdownSound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float StartDelay = 10.f;
	
	UPROPERTY()
	UStartGameWidgetBase* StartGameWidgetInstance = nullptr;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* CountdownSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* CountdownEndSound = nullptr;
};
