// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingWidget.h"
#include "../Building/SpawnableBuilding.h"
#include "Blueprint/WidgetTree.h"
#include "BuildButton.h"
#include "Components/HorizontalBox.h"

void UBuildingWidget::Populate()
{
	for (int i = 0; i < SpawnableBuildings.Num(); i++)
	{
		UBuildButton* NewBuildButton = WidgetTree->ConstructWidget<UBuildButton>(BuildButtonClass);
		BuildingsBox->AddChildToHorizontalBox(NewBuildButton);
	}
	
}

void UBuildingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Populate();
}
