// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetManager.h"

#include "Blueprint/UserWidget.h"
#include "StartGameWidgetBase.h"

void UWidgetManager::Initialize()
{
	StartGameWidgetInstance = CreateWidget<UStartGameWidgetBase>(GetWorld(), StartGameWidget);
	GameOverWidgetInstance = CreateWidget<UGameEndWidgetBase>(GetWorld(), GameOverWidget);
	WinWidgetInstance = CreateWidget<UGameEndWidgetBase>(GetWorld(), WinWidget);
}

UWorld* UWidgetManager::GetWorld() const
{
	if (GetOuter())
	{
		return GetOuter()->GetWorld();
	}
	return nullptr;
}
