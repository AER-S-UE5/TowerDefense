// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildButton.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "BuildingWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/TowerDefenseGameModeBase.h"
#include "TowerDefense/Building/SpawnableBuilding.h"
#include "TowerDefense/Components/PlayerResourcesManager.h"

void UBuildButton::SetBuildingName(FString value)
{
	BuildingName->SetText(FText::FromString(value));
}

void UBuildButton::SetBuildingIcon(UTexture2D* value)
{
	BuildingIcon->SetBrushFromTexture(value, false);
}

void UBuildButton::SetBuildingClass(TSubclassOf<ASpawnableBuilding> value)
{
	BuildingClass = value;
}

void UBuildButton::SetBuildingWidget(UBuildingWidget* Widget)
{
	BuildingWidget = Widget;
}

void UBuildButton::SetGameMode(ATowerDefenseGameModeBase* Value)
{
	GameMode = Value;
	UE_LOG(LogTemp,Warning,TEXT("GameModName"));
}



void UBuildButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BuildButton->OnClicked.AddDynamic(this, &UBuildButton::Build);
}

void UBuildButton::Build()
{
	BuildingWidget->Build(BuildingClass);
}

bool UBuildButton::CheckCostAvailability() const
{
	for (const auto Resource : BuildingClass.GetDefaultObject()->GetCost())
	{
		if(GameMode->GetResourcesManager()->GetResourcePossession(Resource.Key)< Resource.Value) return false;
	}
	return true;
}

void UBuildButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	SetIsEnabled(CheckCostAvailability());
}
