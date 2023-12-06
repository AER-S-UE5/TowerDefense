// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineTemplate.h"
#include "IState.h"



template <typename T, typename U>
StateMachineTemplate<T,U>::StateMachineTemplate()
{
}

template <typename T, typename U>
void StateMachineTemplate<T,U>::Tick(float DeltaTime)
{
	if(const U* ActiveTransition = GetTransition())
	{
		SetState(ActiveTransition->ToState);
		
	}
	if (CurrentState) CurrentState->Tick(DeltaTime);
}

template <typename T, typename U>
void StateMachineTemplate<T,U>::SetState(T* NewState)
{
	if (NewState == CurrentState) return;
    if (CurrentState) CurrentState->OnExit();
	CurrentState = NewState;
	CurrentStateTransitions.Empty();
	if(!Transitions.IsEmpty() && Transitions.Contains(CurrentState))CurrentStateTransitions = Transitions[CurrentState];
	CurrentState->OnEnter();
}

template <typename T, typename U>
T* StateMachineTemplate<T, U>::GetCurrentState() const
{
	return CurrentState;
}

template <typename T, typename U>
void StateMachineTemplate<T,U>::AddTransition(T* FromState, T* ToState, Condition Fun)
{
	TArray<U*> FromStateTransitions;
	if (!Transitions.IsEmpty() && Transitions.Contains(FromState))
	{
		FromStateTransitions = Transitions[FromState];
	}
	U* NewTr = NewObject<U>();
	NewTr->Initialize(Fun, ToState);
	FromStateTransitions.Add(NewTr);
	if(!FromStateTransitions.IsEmpty()) Transitions.Add(FromState, FromStateTransitions);
}

template <typename T, typename U>
void StateMachineTemplate<T,U>::AddFromAnyTransition(T* ToState, Condition Fun)
{
	U* NewTr = NewObject<U>();
	NewTr->Initialize(Fun, ToState);
	FromAnyStateTransitions.Add(NewTr);
}

template <typename T, typename U>
U* StateMachineTemplate<T,U>::GetTransition()
{
	if(!FromAnyStateTransitions.IsEmpty())
	{
		for (auto Transition : FromAnyStateTransitions)
		{
			if(Transition && Transition->Func()) return Transition;
		}
	}

	if(!CurrentStateTransitions.IsEmpty())
	{
		for (auto Transition : CurrentStateTransitions)
		{
			if(Transition && Transition->Func()) return Transition;
		}
	}

	return nullptr;
}

template <typename T>
void STransition<T>::Initialize(Condition Fun, T* NewState)
{
	
	Func = Fun; 
	ToState = NewState;
}

template <typename T>
STransition<T>::STransition()
{
	
	ToState = nullptr;
}
