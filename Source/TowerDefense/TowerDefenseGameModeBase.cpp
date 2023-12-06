// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"
#include "Widgets/BuildingWidget.h"
#include "Building/SpawnableBuilding.h"
#include "GameMode/EndGameModeState.h"
#include "GameMode/GameModeStateMachine.h"
#include "GameMode/PlayGameModeState.h"
#include "Terrain/BuildingTerrainTile.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"
#include "Widgets/EndGameWidget.h"


ATowerDefenseGameModeBase::ATowerDefenseGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
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

void ATowerDefenseGameModeBase::Build(TSubclassOf<ASpawnableBuilding> BuildingClass, ABuildingTerrainTile* TileToBuildOn) const
{
	const USceneComponent* SpawnPoint = BuildingWidget->GetTileToBuildOn()->GetBuildingPoint();
	GetWorld()->SpawnActor<ASpawnableBuilding>(BuildingClass, SpawnPoint->GetComponentLocation(),SpawnPoint->GetComponentRotation());
	HideWidget(BuildingWidget);
	Player->SetPlayerState(APlayerPawn::PlayerState::Default);
}

void ATowerDefenseGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(EndGameResult == None && IsGameLost()) EndGameResult = Lose;
	if(EndGameResult == None && IsGameWon()) EndGameResult = Win;
	StateMachine->Tick(DeltaSeconds);
}

void ATowerDefenseGameModeBase::DecrementEnemiesCount() const
{
	if(UPlayGameModeState* PGM = Cast<UPlayGameModeState> (StateMachine->GetCurrentState()))
	{
		PGM->DecrementEnemiesCount();
	}
}

EGState ATowerDefenseGameModeBase::GetEndGameResult() const
{
	return EndGameResult;
}

void ATowerDefenseGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	EndGameResult = None;
	Player = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	BuildingWidget = CreateGMWidget<UBuildingWidget>(BuildingWidgetClass,"BuildingWidget");
	EndGameWidget = CreateGMWidget<UEndGameWidget>(EndGameWidgetClass, "EndGameWidget");
	SetupStateMachine();
}


void ATowerDefenseGameModeBase::SetupStateMachine()
{
	StateMachine = NewObject<UGameModeStateMachine>();
	PlayGameState = NewObject<UPlayGameModeState>();
	PlayGameState->Initialize(this,SpawnerTowerClass, TargetTowerClass, Levels[CurrentLevelIndex]);
	EndGameState = NewObject<UEndGameModeState>();
	EndGameState->Initialize(this,EndGameWidget);
	StateMachine->AddTransition(PlayGameState,
								EndGameState,
								[this](){return ((this->StateMachine->GetCurrentState()== PlayGameState )&&((this->IsGameLost()||this->IsGameWon())));});
	StateMachine->SetState(PlayGameState);
	
}

bool ATowerDefenseGameModeBase::IsGameWon() const
{
	return (Cast<UPlayGameModeState>(StateMachine->GetCurrentState())->IsGameWon());
}

bool ATowerDefenseGameModeBase::IsGameLost() const
{
	return (Cast<UPlayGameModeState>(StateMachine->GetCurrentState())->IsGameLost());
}

