// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksPlayerController.h"

void ATanksPlayerController::ToggleInput(bool bEnableInput)
{
	auto CachedPawn = GetPawn();
	if (!CachedPawn)
	{
		UE_LOG(LogTemp, Fatal, TEXT("My pawn is null"));
		return;
	}
	
	if (bEnableInput)
	{
		CachedPawn->EnableInput(this);
		return;
	}

	CachedPawn->DisableInput(this);
}
