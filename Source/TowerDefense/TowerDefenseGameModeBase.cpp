// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"
#include "Widgets/BuildingWidget.h"


void ATowerDefenseGameModeBase::CreateBuildingWidget()
{
	BuildingWidget = Cast<UBuildingWidget>(CreateWidget(GetWorld(), BuildingWidgetClass, "BuildingWidget"));
}

void ATowerDefenseGameModeBase::HideWidget(UUserWidget* WidgetToHide)
{
	WidgetToHide->RemoveFromParent();
}

void ATowerDefenseGameModeBase::ShowWidget(UUserWidget* WidgetToShow)
{
	WidgetToShow->AddToViewport();
}

UBuildingWidget* ATowerDefenseGameModeBase::GetBuildingWidget() const
{
	return BuildingWidget;
}

void ATowerDefenseGameModeBase::BeginPlay()
{
	CreateBuildingWidget();
}
