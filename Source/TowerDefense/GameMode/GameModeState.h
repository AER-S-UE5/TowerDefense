// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Utility/IState.h"
#include "GameModeState.generated.h"


class ATowerDefenseGameModeBase;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameModeState : public UIState
{
	GENERATED_BODY()
public:
	void Initialize(ATowerDefenseGameModeBase* GMValue);

protected:
	ATowerDefenseGameModeBase* GetGameMode() const;
private:

	ATowerDefenseGameModeBase* GameMode;
};
