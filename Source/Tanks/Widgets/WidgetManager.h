// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEndWidgetBase.h"
#include "UObject/Object.h"
#include "WidgetManager.generated.h"

class UStartGameWidgetBase;
/**
 * 
 */
UCLASS(Blueprintable)
class TANKS_API UWidgetManager : public UObject
{
	GENERATED_BODY()
public:
	void Initialize();
	UStartGameWidgetBase* GetStartGameWidget() const {return StartGameWidgetInstance;}
	UGameEndWidgetBase* GetWinWidget() const {return WinWidgetInstance;}
	UGameEndWidgetBase* GetGameOverWidget() const {return GameOverWidgetInstance;}

protected:
	virtual UWorld* GetWorld() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameOverWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WinWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UStartGameWidgetBase> StartGameWidget;

	UPROPERTY()
	UStartGameWidgetBase* StartGameWidgetInstance = nullptr;
	
	UPROPERTY()
	UGameEndWidgetBase* GameOverWidgetInstance = nullptr;

	UPROPERTY()
	UGameEndWidgetBase* WinWidgetInstance = nullptr;
};
