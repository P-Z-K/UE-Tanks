// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEndButtonsGroup.h"
#include "Blueprint/UserWidget.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* InfoMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UGameEndButtonsGroup* GameEndButtonsGroup;
};
