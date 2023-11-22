// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildButton.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "BuildingWidget.h"

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

void UBuildButton::NativeOnInitialized()
{
	BuildButton->OnClicked.AddDynamic(this, &UBuildButton::Build);
}

void UBuildButton::Build()
{
	BuildingWidget->Build(BuildingClass);
}
