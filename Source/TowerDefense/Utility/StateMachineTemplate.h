// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"




class UIState;

template<typename  T = UIState, typename V = UObject>
class STransition 
{
public:

	UPROPERTY()
	bool(V::*Func)();
	V* Caller;
	T* ToState;
	void Initialize(bool(V::*Fun) (), T* NewState, V* Value);
};


template<typename T = UIState , typename V=UObject, typename U = STransition<T,V>>
class StateMachineTemplate
{
	public:
	StateMachineTemplate();

	T* GetCurrentState() const;
	void UpdateTick(float DeltaTime);
	void SetState(T* NewState);
	void AddTransition(T* FromState, T* ToState,bool(V::*Fun) (), V* Value);
	void AddFromAnyTransition(T* ToState, bool(V::*Fun) (), V* Value);
private:

	T* CurrentState;
	
	UPROPERTY()
	TMap<T*, TArray<U*>> Transitions;
	
	TArray<U*> CurrentStateTransitions;
	TArray<U*> FromAnyStateTransitions;

	U* GetTransition();	
};

template <typename T, typename V, typename U>
StateMachineTemplate<T,V,U>::StateMachineTemplate()
{
}

template <typename T, typename V, typename U>
void StateMachineTemplate<T,V,U>::UpdateTick(float DeltaTime)
{
	if(const U* ActiveTransition = GetTransition())
	{
		SetState(ActiveTransition->ToState);
		
	}
	if (CurrentState) CurrentState->UpdateTick(DeltaTime);
}

template <typename T, typename V, typename U>
void StateMachineTemplate<T,V,U>::SetState(T* NewState)
{
	if (NewState == CurrentState) return;
    if (CurrentState) CurrentState->OnExit();
	CurrentState = NewState;
	CurrentStateTransitions.Empty();
	if(!Transitions.IsEmpty() && Transitions.Contains(CurrentState))CurrentStateTransitions = Transitions[CurrentState];
	CurrentState->OnEnter();
}

template <typename T, typename U, typename V>
T* StateMachineTemplate<T,U,V>::GetCurrentState() const
{
	return CurrentState;
}

template <typename T, typename V, typename U>
void StateMachineTemplate<T,V,U>::AddTransition(T* FromState, T* ToState, bool(V::*Fun) (), V* Value)
{
	TArray<U*> FromStateTransitions;
	if (!Transitions.IsEmpty() && Transitions.Contains(FromState))
	{
		FromStateTransitions = Transitions[FromState];
	}
	U* NewTr = NewObject<U>(Value);
	NewTr->Initialize(Fun, ToState, Value);
	FromStateTransitions.Add(NewTr);
	if(!FromStateTransitions.IsEmpty()) Transitions.Add(FromState, FromStateTransitions);
}

template <typename T, typename V, typename U>
void StateMachineTemplate<T,V,U>::AddFromAnyTransition(T* ToState, bool(V::*Fun) (), V* Value)
{
	U* NewTr = NewObject<U>(Value);
	NewTr->Initialize(Fun, ToState, Value);
	FromAnyStateTransitions.Add(NewTr);
}

template <typename T, typename V, typename U>
U* StateMachineTemplate<T,V,U>::GetTransition()
{
	if(!FromAnyStateTransitions.IsEmpty())
	{
		for (auto Transition : FromAnyStateTransitions)
		{
			if(Transition)
			{
				if(std::invoke(Transition->Func,Transition->Caller)) return Transition;
			}
		}
	}

	if(!CurrentStateTransitions.IsEmpty())
	{
		for (auto Transition : CurrentStateTransitions)
		{
			if(Transition)
			{
				if(std::invoke(Transition->Func,Transition->Caller)) return Transition;
			}
		}
	}

	return nullptr;
}

template <typename T, typename V>
void STransition<T,V>::Initialize(bool(V::*Fun)() , T* NewState, V* Value)
{
	
	Func = Fun;
	Caller = Value;
	ToState = NewState;
}



//template <typename T>
// STransition<T>::STransition()
// {
// 	
// 	ToState = nullptr;
// }






