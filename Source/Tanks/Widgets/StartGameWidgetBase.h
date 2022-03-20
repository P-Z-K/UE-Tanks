// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "StartGameWidgetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCountdownEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateUI);
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
	
	UPROPERTY(VisibleAnywhere, BlueprintCallable, BlueprintAssignable)
	FOnUpdateUI OnUpdateUI;

	UFUNCTION(BlueprintImplementableEvent)
	void StartCountdown(float Time);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* CountdownText = nullptr;
};
