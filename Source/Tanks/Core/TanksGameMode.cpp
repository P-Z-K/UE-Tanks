// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "TanksPlayerController.h"
#include "Tanks/Audio/AudioManager.h"
#include "Tanks/Enemy/EnemiesSubsystem.h"
#include "Tanks/Pawns/Tank.h"
#include "Tanks/Widgets/StartGameWidgetBase.h"

ATanksGameMode::ATanksGameMode()
{
}

void ATanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	AudioManagerInstance = NewObject<UAudioManager>(this, AudioManager);
	
	WidgetManagerInstance = NewObject<UWidgetManager>(this, WidgetManager);
	WidgetManagerInstance->Initialize();
	
	HandlePreStart();
}

void ATanksGameMode::HandlePreStart()
{
	DisplayCountdown();
	PrepareLevel();
}

void ATanksGameMode::DisplayCountdown()
{
	WidgetManagerInstance->GetStartGameWidget()->AddToViewport();
	WidgetManagerInstance->GetStartGameWidget()->OnCountdownEnded.AddDynamic(this, &ATanksGameMode::HandleGameStart);
	WidgetManagerInstance->GetStartGameWidget()->OnUpdateUI.AddDynamic(this, &ATanksGameMode::PlayCountdownSound);
	WidgetManagerInstance->GetStartGameWidget()->StartCountdown(StartDelay);
}

void ATanksGameMode::PlayCountdownSound()
{
	AudioManagerInstance->PlayClockSound();
}

void ATanksGameMode::PrepareLevel()
{
	PlayerController = Cast<ATanksPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Fatal, TEXT("PlayerController is null"));
		return;
	}

	PlayerController->ToggleInput(false);
	PlayerController->SetVisibility(false);
	PlayerController->ToggleTicking(false);
	PlayerController->ResetDeathState();
}

void ATanksGameMode::HandleGameStart()
{
	AudioManagerInstance->PlayCountdownEndSound();
	AudioManagerInstance->PlayBackgroundMusic();

	WidgetManagerInstance->GetStartGameWidget()->RemoveFromViewport();
	
	
	EnablePlayer();

	Player = Cast<ATank>(PlayerController->GetPawn());

	Player->OnTankDie.AddUObject(this, &ATanksGameMode::HandleGameOver);
	GetWorld()->GetSubsystem<UEnemiesSubsystem>()->OnAllEnemiesDied.AddUObject(this, &ATanksGameMode::HandleWin);
}

void ATanksGameMode::EnablePlayer()
{
	PlayerController->ToggleTicking(true);
	PlayerController->SetVisibility(false);
	PlayerController->ToggleInput(true);
}

void ATanksGameMode::HandleGameOver()
{
	HandleGameEnd();
	WidgetManagerInstance->GetGameOverWidget()->AddToViewport();
}

void ATanksGameMode::HandleGameEnd()
{
	WidgetManagerInstance->GetStartGameWidget()->OnCountdownEnded.RemoveAll(this);
	GetWorld()->GetGameViewport()->RemoveAllViewportWidgets();
	AudioManagerInstance->StopBackgroundMusic();
	DisablePlayer();
}

void ATanksGameMode::DisablePlayer()
{
	GetWorld()->GetSubsystem<UEnemiesSubsystem>()->OnAllEnemiesDied.RemoveAll(this);
	Player->OnTankDie.RemoveAll(this);
	PlayerController->ToggleTicking(false);
	PlayerController->SetVisibility(true);
	PlayerController->ToggleInput(false);
}

void ATanksGameMode::HandleWin()
{
	WidgetManagerInstance->GetWinWidget()->AddToViewport();
}


