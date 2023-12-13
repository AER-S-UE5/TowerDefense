// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"
#include "Widgets/BuildingWidget.h"
#include "Building/SpawnableBuilding.h"
#include "Components/PlayerResourcesManager.h"
#include "Components/StateMachineComponent.h"
#include "GameMode/EndGameModeState.h"
#include "GameMode/PlayGameModeState.h"
#include "Terrain/BuildingTerrainTile.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"
#include "Widgets/EndGameWidget.h"
#include "Widgets/GameTitleBar.h"


ATowerDefenseGameModeBase::ATowerDefenseGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	PlayerResourcesManager = CreateDefaultSubobject<UPlayerResourcesManager>("Player Resources Manager");
	StateMachine = CreateDefaultSubobject<UStateMachineComponent>("Game Mode State Machine");
	
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

UPlayerResourcesManager* ATowerDefenseGameModeBase::GetResourcesManager() const
{
	return PlayerResourcesManager;
}


void ATowerDefenseGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	EndGameResult = None;
	Player = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	BuildingWidget = CreateGMWidget<UBuildingWidget>(BuildingWidgetClass,"BuildingWidget");
	EndGameWidget = CreateGMWidget<UEndGameWidget>(EndGameWidgetClass, "EndGameWidget");
	TitleBarWidget = CreateGMWidget<UGameTitleBar>(GameTitleBarClass, "TitleBarWidget");
	TitleBarWidget->SetGameMode(this);
	TitleBarWidget->Populate({GoldCoins});
	TitleBarWidget->AddToViewport();
	SetupStateMachine();
}


void ATowerDefenseGameModeBase::SetupStateMachine()
{
	PlayGameState = NewObject<UPlayGameModeState>(this);
	PlayGameState->Initialize(this,SpawnerTowerClass, TargetTowerClass, Levels[CurrentLevelIndex]);
	EndGameState = NewObject<UEndGameModeState>(this);
	EndGameState->Initialize(this,EndGameWidget);
	StateMachine->AddTransition(PlayGameState,EndGameState, [&](){return (IsGameWon()||IsGameLost());});
	StateMachine->SetCurrentState(PlayGameState);
	
}

bool ATowerDefenseGameModeBase::IsGameWon() const
{
	return (Cast<UPlayGameModeState>(StateMachine->GetCurrentState())->IsGameWon());
}

bool ATowerDefenseGameModeBase::IsGameLost() const
{
	return (Cast<UPlayGameModeState>(StateMachine->GetCurrentState())->IsGameLost());
}

