// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EndGameMessage;

	UPROPERTY(meta = (BindWidget))
	class UButton* NextLevelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ReplayButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	void PlayNextLevel();
	void ReplayLevel();
	void QuitGame();
};
