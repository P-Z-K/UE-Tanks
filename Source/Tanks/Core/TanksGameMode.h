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

public:
	void DisplayCountdown();
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float StartDelay = 10.f;

	UPROPERTY()
	UStartGameWidgetBase* StartGameWidgetInstance = nullptr;
	
	void PrepareLevel();
	UFUNCTION()
	void HandleGameStart();
	
	void LaunchPlayer();
	void HandleGameOver();
	void HandleWin();

	void DisablePlayer();

	UPROPERTY()
	ATanksPlayerController* PlayerController = nullptr;
	UPROPERTY()
	ATank* Player = nullptr;

	UPROPERTY()
	UUserWidget* GameOverWidgetInstance = nullptr;
	UPROPERTY()
	UUserWidget* WinWidgetInstance = nullptr;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameOverWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WinWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UStartGameWidgetBase> CountdownWidget;
};
