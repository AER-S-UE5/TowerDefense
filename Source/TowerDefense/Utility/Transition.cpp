// Fill out your copyright notice in the Description page of Project Settings.


#include "Transition.h"

void UTransition::Setup(TFunction<bool()> Func, UIState* Value)
{
	Condition = Func;
	ToState = Value;
	AddToRoot();
}
