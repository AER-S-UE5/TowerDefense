// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utility/LevelData.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenseGameModeBase.generated.h"


class UStateMachineComponent;

enum EGState
{
	None,
	Lose,
	Win
};

class UGameTitleBar;
class UBuildingWidget;
class UEndGameWidget;
class ASpawnableBuilding;
class UGameModeStateMachine;
class UPlayGameModeState;
class UEndGameModeState;
class UPlayerResourcesManager;
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
	UPlayerResourcesManager* GetResourcesManager() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UPlayerResourcesManager* PlayerResourcesManager;
	
	UPROPERTY(VisibleAnywhere)
	UStateMachineComponent* StateMachine;
	
	UPROPERTY(EditDefaultsOnly, Category ="Widgets")
	TSubclassOf<UBuildingWidget> BuildingWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UEndGameWidget> EndGameWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UGameTitleBar> GameTitleBarClass;

	UPROPERTY(EditDefaultsOnly, Category ="Levels")
	TArray<FLevelData> Levels;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	int32 CurrentLevelIndex = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<class ASpawnerTower> SpawnerTowerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<class ATargetTower> TargetTowerClass;

	UPROPERTY()
	UBuildingWidget* BuildingWidget;
	UPROPERTY()
	UEndGameWidget* EndGameWidget;
	UPROPERTY()
	UGameTitleBar* TitleBarWidget;

	UPROPERTY()
	UPlayGameModeState* PlayGameState;
	UPROPERTY()
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

