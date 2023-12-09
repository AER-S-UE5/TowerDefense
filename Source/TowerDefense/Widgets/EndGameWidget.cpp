// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


void UEndGameWidget::SetGameMode(ATowerDefenseGameModeBase* value)
{
	GameMode = value;
}

void UEndGameWidget::SetEndGameWidget(UEndGameWidget* value)
{
	EndGameWidget = value;
}

void UEndGameWidget::SetEndGameMessage(const FString& Value) const
{
	EndGameMessage->SetText(FText::FromString(Value));
}

void UEndGameWidget::SetEndGameMessageColor(FColor color) const
{
	EndGameMessage->SetColorAndOpacity(FSlateColor(color));
}

void UEndGameWidget::NativeOnInitialized()
{
	NextLevelButton->OnClicked.AddDynamic(this, &UEndGameWidget::PlayNextLevel);
	ReplayButton->OnClicked.AddDynamic(this, &UEndGameWidget::ReplayLevel);
	QuitButton->OnClicked.AddDynamic(this, &UEndGameWidget::QuitGame);
}

void UEndGameWidget::PlayNextLevel()
{

}

void UEndGameWidget::ReplayLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(),FName( UGameplayStatics::GetCurrentLevelName(this)));
}

void UEndGameWidget::QuitGame()
{

}
