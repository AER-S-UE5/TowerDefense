// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Transition.generated.h"

class UIState;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTransition : public UObject
{
	GENERATED_BODY()
public:
	
	TFunction<bool()> Condition;

	UPROPERTY()
	UIState* ToState;

	void Setup(TFunction<bool()> Func, UIState* Value);
};
