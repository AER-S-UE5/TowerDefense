// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Utility/StateMachineTemplate.h"
#include "GameModeTransition.generated.h"

class UGameModeState;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameModeTransition : public UObject, public STransition<UGameModeState>
{
	GENERATED_BODY()

};
