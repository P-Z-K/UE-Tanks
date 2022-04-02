// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEndButtonsGroup.h"
#include "Blueprint/UserWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "GameEndWidgetBase.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class TANKS_API UGameEndWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE UGameEndButtonsGroup* GetGameEndButtonsGroup() const {return GameEndButtonsGroup;}

protected:
	UFUNCTION(BlueprintCallable)
	void ToggleButtonsInteraction(ESlateVisibility NewVisiblity);

	
	UPROPERTY(Transient, BlueprintReadWrite, meta=(BindWidgetAnim))
	UWidgetAnimation* ButtonsGroupFadeInAnim;

	UPROPERTY(Transient, BlueprintReadWrite, meta=(BindWidgetAnim))
	UWidgetAnimation* FadeInAnim;

	UPROPERTY(Transient, BlueprintReadWrite, meta=(BindWidgetAnim))
	UWidgetAnimation* MovingVerticalSliderAnim;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* InfoMessage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* FadingInBackground;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* MovingVerticalSlider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBackgroundBlur* BlurredBackground;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UGameEndButtonsGroup* GameEndButtonsGroup;
};
