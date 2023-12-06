// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IState.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UIState : public UObject
{
	GENERATED_BODY()
public:
	virtual void OnEnter(){};
	virtual void OnExit() {};
	virtual void Tick(float DeltaTime){};

};
