// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameEndButtonsGroup.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class TANKS_API UGameEndButtonsGroup : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE UButton* GetAgreeButton() const {return AgreeButton;}
	FORCEINLINE UButton* GetDisagreeButton() const {return DisagreeButton;}
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* AgreeButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* DisagreeButton;
};
