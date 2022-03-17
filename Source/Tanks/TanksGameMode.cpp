// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameMode.h"

#include "EnemiesSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "TanksPlayerController.h"

void ATanksGameMode::DisplayCountdown()
{
	StartGameWidgetInstance = CreateWidget<UStartGameWidgetBase>(GetWorld(), CountdownWidget);
	StartGameWidgetInstance->AddToViewport();
	StartGameWidgetInstance->StartCountdown(StartDelay);
	StartGameWidgetInstance->OnCountdownEnded.AddDynamic(this, &ATanksGameMode::HandleGameStart);
}

void ATanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	DisplayCountdown();
	PrepareLevel();
}

void ATanksGameMode::PrepareLevel()
{
	PlayerController = Cast<ATanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!PlayerController)
		return;

	PlayerController->ToggleInput(false);
	PlayerController->SetVisibility(false);
	PlayerController->ToggleTicking(false);
	PlayerController->ResetDeathState();
}

void ATanksGameMode::HandleGameStart()
{
	StartGameWidgetInstance->RemoveFromViewport();
	LaunchPlayer();
	
	Player = Cast<ATank>(PlayerController->GetPawn());

	Player->OnTankDie.AddUObject(this, &ATanksGameMode::HandleGameOver);
	GetWorld()->GetSubsystem<UEnemiesSubsystem>()->OnAllEnemiesDied.AddUObject(this, &ATanksGameMode::HandleWin);
	
	GameOverWidgetInstance = CreateWidget<UUserWidget>(PlayerController, GameOverWidget);
	WinWidgetInstance = CreateWidget<UUserWidget>(PlayerController, WinWidget);
}

void ATanksGameMode::LaunchPlayer()
{
	PlayerController->ToggleTicking(true);
	PlayerController->SetVisibility(false);
	PlayerController->ToggleInput(true);
}

void ATanksGameMode::HandleGameOver()
{
	StartGameWidgetInstance->OnCountdownEnded.RemoveAll(this);
	GetWorld()->GetGameViewport()->RemoveAllViewportWidgets();
	GameOverWidgetInstance->AddToViewport();
	DisablePlayer();
}

void ATanksGameMode::HandleWin()
{
	GetWorld()->GetGameViewport()->RemoveAllViewportWidgets();
	WinWidgetInstance->AddToViewport();
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
