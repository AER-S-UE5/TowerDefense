// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"



class ATowerDefenseGameModeBase;
class UEndGameWidget;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetGameMode(ATowerDefenseGameModeBase * value);
	void SetEndGameWidget(UEndGameWidget * value);
	void SetEndGameMessage(const FString& Value) const;
	void SetEndGameMessageColor(FColor color) const;
	
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

	ATowerDefenseGameModeBase* GameMode;

	UEndGameWidget* EndGameWidget;
	
	void PlayNextLevel();
	void ReplayLevel();
	void QuitGame();
};
