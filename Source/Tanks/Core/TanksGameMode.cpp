// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "TanksPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Tanks/Enemy/EnemiesSubsystem.h"
#include "Tanks/Pawns/Tank.h"
#include "Tanks/Widgets/StartGameWidgetBase.h"

void ATanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandlePreStart();
}

void ATanksGameMode::HandlePreStart()
{
	DisplayCountdown();
	PrepareLevel();
}

void ATanksGameMode::DisplayCountdown()
{
	StartGameWidgetInstance = CreateWidget<UStartGameWidgetBase>(GetWorld(), CountdownWidget);
	StartGameWidgetInstance->AddToViewport();
	StartGameWidgetInstance->OnCountdownEnded.AddDynamic(this, &ATanksGameMode::HandleGameStart);
	StartGameWidgetInstance->OnUpdateUI.AddDynamic(this, &ATanksGameMode::PlayCountdownSound);
	StartGameWidgetInstance->StartCountdown(StartDelay);
}

void ATanksGameMode::PlayCountdownSound()
{
	if (CountdownSound)
	{
		auto Location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(this, CountdownSound, Location);
		UE_LOG(LogTemp, Warning, TEXT("cluck"));
	}
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
	if (StartGameWidgetInstance)
	{
		StartGameWidgetInstance->RemoveFromViewport();
	}

	if (CountdownEndSound)
	{
		auto Location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(this, CountdownEndSound, Location);
	}
	
	EnablePlayer();

	Player = Cast<ATank>(PlayerController->GetPawn());

	Player->OnTankDie.AddUObject(this, &ATanksGameMode::HandleGameOver);
	GetWorld()->GetSubsystem<UEnemiesSubsystem>()->OnAllEnemiesDied.AddUObject(this, &ATanksGameMode::HandleWin);

	GameOverWidgetInstance = CreateWidget<UUserWidget>(PlayerController, GameOverWidget);
	WinWidgetInstance = CreateWidget<UUserWidget>(PlayerController, WinWidget);
}

void ATanksGameMode::EnablePlayer()
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
	GetWorld()->GetGameViewport()->RemoveAllViewportWidgets();
	WinWidgetInstance->AddToViewport();
	DisablePlayer();
}


