// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeState.h"

void UGameModeState::Initialize(ATowerDefenseGameModeBase* GMValue)
{
	GameMode = GMValue;
}

ATowerDefenseGameModeBase* UGameModeState::GetGameMode() const
{
	return GameMode;
}
