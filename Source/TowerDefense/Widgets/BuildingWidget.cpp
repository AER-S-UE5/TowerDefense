// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingWidget.h"
#include "../Building/SpawnableBuilding.h"
#include "Blueprint/WidgetTree.h"
#include "BuildButton.h"
#include "Components/HorizontalBox.h"
#include "../Terrain/BuildingTerrainTile.h"
#include "TowerDefense/TowerDefenseGameModeBase.h"

void UBuildingWidget::Populate(ATowerDefenseGameModeBase* GameMode)
{
	TDGameMode = GameMode;
	TArray<TSubclassOf<ASpawnableBuilding>> SpawnableBuildingsKeys;
	int32 SpawnableBuildingsElements = SpawnableBuildings.GetKeys(SpawnableBuildingsKeys);
	for (int i = 0; i < SpawnableBuildingsElements; i++)
	{
		UBuildButton* NewBuildButton = WidgetTree->ConstructWidget<UBuildButton>(BuildButtonClass);
		UClass* buildingClass = *SpawnableBuildingsKeys[i];
		FString BuildingName = Cast<ASpawnableBuilding>(buildingClass->GetDefaultObject())->GetBuildingClassName();
		NewBuildButton->SetBuildingName(BuildingName);
		NewBuildButton->SetBuildingClass(SpawnableBuildingsKeys[i]);
		NewBuildButton->SetBuildingWidget(this);
		NewBuildButton->SetGameMode(TDGameMode);
		if (SpawnableBuildings[SpawnableBuildingsKeys[i]]) NewBuildButton->SetBuildingIcon(SpawnableBuildings[SpawnableBuildingsKeys[i]]);
		BuildingsBox->AddChildToHorizontalBox(NewBuildButton);
	}
	
}



void UBuildingWidget::SetTileToBuildOn(class ABuildingTerrainTile* value)
{
	TileToBuildOn = value;
}

ABuildingTerrainTile* UBuildingWidget::GetTileToBuildOn() const
{
	return TileToBuildOn;
}



void UBuildingWidget::Build(TSubclassOf<ASpawnableBuilding> BuildingClass)
{
	TDGameMode->Build(BuildingClass, TileToBuildOn);
}

void UBuildingWidget::SetGameMode(ATowerDefenseGameModeBase* value)
{
	TDGameMode = value;
}

void UBuildingWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UBuildingWidget::NativeOnInitialized()
{
	Super::OnInitialized();
}


