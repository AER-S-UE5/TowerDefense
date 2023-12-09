// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Utility/StateMachineTemplate.h"
#include "GameModeStateMachine.generated.h"

class ATowerDefenseGameModeBase;
class UGameModeState;
class UGameModeTransition;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameModeStateMachine : public UActorComponent, public StateMachineTemplate<UGameModeState,ATowerDefenseGameModeBase,UGameModeTransition>
{
	GENERATED_BODY()
	
};
