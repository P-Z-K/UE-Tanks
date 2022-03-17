// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksPlayerController.h"

#include "Tank.h"

void ATanksPlayerController::ToggleInput(bool bEnableInput)
{
	auto CachedPawn = GetPawn();
	if (bEnableInput)
	{
		CachedPawn->EnableInput(this);
		return;
	}

	CachedPawn->DisableInput(this);
}
