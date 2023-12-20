// Fill out your copyright notice in the Description page of Project Settings.


#include "MaiMenuGameMode.h"

#include "Blueprint/UserWidget.h"
#include "TowerDefense/Widgets/MainMenuWidget.h"

void AMaiMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	MainMenu = Cast<UMainMenuWidget>(CreateWidget(GetWorld(),MainMenuWidgetClass,"Main Menu"));
	MainMenu->AddToViewport();
}
