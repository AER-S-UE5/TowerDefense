// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utility/LevelData.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenseGameModeBase.generated.h"

enum EGState
{
	None,
	Lose,
	Win
};

class UBuildingWidget;
class UEndGameWidget;
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
	static void HideWidget(UUserWidget* WidgetToHide);
	static void ShowWidget(UUserWidget* WidgetToShow);
	UBuildingWidget* GetBuildingWidget() const;
	void Build(TSubclassOf<ASpawnableBuilding> BuildingClass,class ABuildingTerrainTile* TileToBuildOn) const;
	virtual void Tick(float DeltaSeconds) override;
	void DecrementEnemiesCount() const;
	EGState GetEndGameResult() const;


protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category ="Widgets")
	TSubclassOf<UBuildingWidget> BuildingWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UEndGameWidget> EndGameWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category ="Levels")
	TArray<FLevelData> Levels;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	int32 CurrentLevelIndex = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<class ASpawnerTower> SpawnerTowerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<class ATargetTower> TargetTowerClass;


	UBuildingWidget* BuildingWidget;
	UEndGameWidget* EndGameWidget;

	UGameModeStateMachine* StateMachine;
	UPlayGameModeState* PlayGameState;
	UEndGameModeState* EndGameState;

	EGState EndGameResult;

	class APlayerPawn* Player;

	template<typename T= UUserWidget>
	T* CreateGMWidget(TSubclassOf<T> Class, FName Name);
	

	bool IsGameLost() const;
	bool IsGameWon() const;

	void SetupStateMachine();
};

template <typename T>
T* ATowerDefenseGameModeBase::CreateGMWidget(TSubclassOf<T> Class, FName Name)
{
	T* GMWidget = Cast<T>( CreateWidget(GetWorld(),Class,Name));
	GMWidget->SetGameMode(this);
	return GMWidget;
}

