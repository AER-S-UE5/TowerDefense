// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeState.h"
#include "TowerDefense/Widgets/EndGameWidget.h"
#include "EndGameModeState.generated.h"

class ATowerDefenseGameModeBase;
class UEndGameWidget;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UEndGameModeState : public UGameModeState
{
	GENERATED_BODY()
public:
	void Initialize(ATowerDefenseGameModeBase* GM, UEndGameWidget* EGW);
	virtual void OnEnter() override;
	virtual void Tick(float DeltaTime) override;
private:
	ATowerDefenseGameModeBase* GameMode;
	UEndGameWidget* EndGameWidget;
};
