// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "StartGameWidgetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCountdownEnded);
/**
 * 
 */
UCLASS()
class TANKS_API UStartGameWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintCallable, BlueprintAssignable)
	FOnCountdownEnded OnCountdownEnded;

	UFUNCTION(BlueprintImplementableEvent)
	void StartCountdown(float Time);

protected:
	UFUNCTION(BlueprintCallable)
	void OnCountdownEnd();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateUI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* CountdownText = nullptr;
};
