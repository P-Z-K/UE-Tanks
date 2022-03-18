// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TanksPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATanksPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	bool IsDied = false;

public:
	void ToggleInput(bool bInputEnabled);
	void SetVisibility(bool bShouldBeHidden) const {GetPawn()->SetActorHiddenInGame(bShouldBeHidden);}
	void ToggleTicking(bool bShouldTick) const {GetPawn()->SetActorTickEnabled(bShouldTick);}
	bool HasDied() const {return IsDied;}
	void ResetDeathState() {IsDied = false;}
};
