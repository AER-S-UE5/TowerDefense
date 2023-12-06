// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameModeState.h"

#include "TowerDefense/TowerDefenseGameModeBase.h"

void UEndGameModeState::Initialize(ATowerDefenseGameModeBase* GM, UEndGameWidget* EGW)
{
	GameMode = GM;
	EndGameWidget = EGW;
}

void UEndGameModeState::OnEnter()
{
	Super::OnEnter();
	switch (GameMode->GetEndGameResult())
	{
	case EGState::Win:
		EndGameWidget->SetEndGameMessage("YOU WIN");
		EndGameWidget->SetEndGameMessageColor(FColor::Green);
		break;
	case EGState::Lose:
		EndGameWidget->SetEndGameMessage("YOU LOSE");
		EndGameWidget->SetEndGameMessageColor(FColor::Red);
		break;
	default:
		break;;
	}

	EndGameWidget->AddToViewport();
}

void UEndGameModeState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
