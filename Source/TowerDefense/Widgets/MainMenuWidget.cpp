// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "MenuButton.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "../TowerDefenseGameModeBase.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PlayButton->OnClickDelegate.BindUFunction(this,FName("Continue"));
}

void UMainMenuWidget::Continue()
{
	UGameplayStatics::OpenLevel(GetWorld(),"M_TestMap",true);
}
