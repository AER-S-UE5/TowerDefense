// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utility/LevelData.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenseGameModeBase.generated.h"

class UBuildingWidget;
class ASpawnableBuilding;
class UGameModeStateMachine;
class UPlayGameModeState;
class UEndGameModeState;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerDefenseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATowerDefenseGameModeBase();
	void CreateBuildingWidget();
	static void HideWidget(UUserWidget* WidgetToHide);
	static void ShowWidget(UUserWidget* WidgetToShow);
	UBuildingWidget* GetBuildingWidget() const;
	void Build(TSubclassOf<ASpawnableBuilding> BuildingClass,class ABuildingTerrainTile* TileToBuildOn) const;
	virtual void Tick(float DeltaSeconds) override;
	void DecrementEnemiesCount();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category ="Widgets")
	TSubclassOf<UBuildingWidget> BuildingWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category ="Levels")
	TArray<FLevelData> Levels;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	int32 CurrentLevelIndex = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<class ASpawnerTower> SpawnerTowerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<class ATargetTower> TargetTowerClass;


	UBuildingWidget* BuildingWidget;

	UGameModeStateMachine* StateMachine;
	UPlayGameModeState* PlayGameState;
	UEndGameModeState* EndGameState;
	

	class APlayerPawn* Player;
	

	bool IsGameLost() ;
	bool IsGameWon() ;

	void SetupStateMachine();
};
