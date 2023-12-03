// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameWidget.h"
#include "Components/TextBlock.h"



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

}

void UEndGameWidget::QuitGame()
{

}
