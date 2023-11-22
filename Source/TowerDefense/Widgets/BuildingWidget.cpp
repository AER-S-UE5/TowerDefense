// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingWidget.h"
#include "../Building/SpawnableBuilding.h"
#include "Blueprint/WidgetTree.h"
#include "BuildButton.h"
#include "Components/HorizontalBox.h"

void UBuildingWidget::Populate()
{
	TArray<TSubclassOf<ASpawnableBuilding>> SpawnableBuildingsKeys;
	int32 SpawnableBuildingsElements = SpawnableBuildings.GetKeys(SpawnableBuildingsKeys);
	for (int i = 0; i < SpawnableBuildingsElements; i++)
	{
		UBuildButton* NewBuildButton = WidgetTree->ConstructWidget<UBuildButton>(BuildButtonClass);
		UClass* buildingClass = *SpawnableBuildingsKeys[i];
		FString BuildingName = Cast<ASpawnableBuilding>(buildingClass->GetDefaultObject())->GetBuildingClassName();
		NewBuildButton->SetBuildingName(BuildingName);
		NewBuildButton->SetBuildingClass(SpawnableBuildingsKeys[i]);
		if (SpawnableBuildings[SpawnableBuildingsKeys[i]]) NewBuildButton->SetBuildingIcon(SpawnableBuildings[SpawnableBuildingsKeys[i]]);
		BuildingsBox->AddChildToHorizontalBox(NewBuildButton);
	}
	
}

void UBuildingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Populate();
}
