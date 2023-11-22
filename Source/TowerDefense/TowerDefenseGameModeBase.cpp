// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"
#include "Widgets/BuildingWidget.h"
#include "Building/SpawnableBuilding.h"
#include "Terrain/BuildingTerrainTile.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"


void ATowerDefenseGameModeBase::CreateBuildingWidget()
{
	BuildingWidget = Cast<UBuildingWidget>(CreateWidget(GetWorld(), BuildingWidgetClass, "BuildingWidget"));
	BuildingWidget->SetGameMode(this);
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

void ATowerDefenseGameModeBase::Build(TSubclassOf<ASpawnableBuilding> BuildingClass, ABuildingTerrainTile* TileToBuildOn)
{
	USceneComponent* SpawnPoint = BuildingWidget->GetTileToBuildOn()->GetBuildingPoint();
	GetWorld()->SpawnActor<ASpawnableBuilding>(BuildingClass, SpawnPoint->GetComponentLocation(),SpawnPoint->GetComponentRotation());
	HideWidget(BuildingWidget);
	Player->SetPlayerState(APlayerPawn::PlayerState::Default);
}

void ATowerDefenseGameModeBase::BeginPlay()
{
	Player = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	CreateBuildingWidget();
}
