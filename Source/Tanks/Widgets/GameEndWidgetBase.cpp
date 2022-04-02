// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEndWidgetBase.h"

void UGameEndWidgetBase::ToggleButtonsInteraction(ESlateVisibility NewVisiblity)
{
	GameEndButtonsGroup->SetVisibility(NewVisiblity);
}
