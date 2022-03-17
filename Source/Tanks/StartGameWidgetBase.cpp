// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameWidgetBase.h"

void UStartGameWidgetBase::OnCountdownEnd()
{
	OnCountdownEnded.Broadcast();
}
