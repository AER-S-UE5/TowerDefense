// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <functional>
using Condition = std::function<bool()>;

class UIState;

template<typename  T = UIState>
class STransition 
{
public:
	
	Condition Func;
	T* ToState;
	STransition();
	void Initialize(Condition Fun, T* NewState);
};


template<typename T = UIState, typename U = STransition<T>>
class StateMachineTemplate
{
	public:
	StateMachineTemplate();

	T* GetCurrentState() const;
	void Tick(float DeltaTime);
	void SetState(T* NewState);
	void AddTransition(T* FromState, T* ToState,Condition Fun);
	void AddFromAnyTransition(T* ToState, Condition Fun);
private:

	T* CurrentState;
	TMap<T*, TArray<U*>> Transitions;
	TArray<U*> CurrentStateTransitions;
	TArray<U*> FromAnyStateTransitions;

	U* GetTransition();	
};






