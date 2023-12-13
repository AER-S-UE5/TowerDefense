// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineComponent.h"

#include "TowerDefense/Utility/Transition.h"

UIState* UStateMachineComponent::GetCurrentState() const
{
	return CurrentState;
}

void UStateMachineComponent::SetCurrentState(UIState* NewState)
{
	if (NewState == CurrentState) return;
	if (CurrentState) CurrentState->OnExit();
	CurrentState = NewState;
	CurrentStateTransitions.Empty();
	if(!StatesTransitions.IsEmpty() && StatesTransitions.Contains(CurrentState))CurrentStateTransitions = StatesTransitions[CurrentState];
	CurrentState->OnEnter();
}

void UStateMachineComponent::AddTransition(UIState* FromState, UIState* ToState, TFunction<bool()> Func)
{
	TArray<UTransition*> FromStateTransitions;
	if (!StatesTransitions.IsEmpty() && StatesTransitions.Contains(FromState))
	{
		FromStateTransitions = StatesTransitions[FromState];
	}
	UTransition* NewTr = NewObject<UTransition>();
	NewTr->Setup(Func, ToState);
	FromStateTransitions.Add(NewTr);
	if(!FromStateTransitions.IsEmpty()) StatesTransitions.Add(FromState, FromStateTransitions);
}

void UStateMachineComponent::AddFromAnyTransition(UIState* ToState, TFunction<bool()> Func)
{
	UTransition* NewTr = NewObject<UTransition>();
	NewTr->Setup(Func, ToState);
	FromAnyTransitions.Add(NewTr);
}

UStateMachineComponent::~UStateMachineComponent()
{
	if (!StatesTransitions.IsEmpty())
	{
		for (auto Element : StatesTransitions)
		{
			for (const auto Transition : Element.Value)
			{
				Transition->RemoveFromRoot();
			}
		}
	}
	if(!FromAnyTransitions.IsEmpty())
	{
		for (const auto Transition : FromAnyTransitions)
		{
			Transition->RemoveFromRoot();
		}
	}
}

// Sets default values for this component's properties
UStateMachineComponent::UStateMachineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

UTransition* UStateMachineComponent::GetTransition() const
{
	if(!FromAnyTransitions.IsEmpty())
	{
		for (const auto Transition : FromAnyTransitions)
		{
			if(Transition && Transition->Condition())
			{
				return Transition;
			}
		}
	}

	if(!CurrentStateTransitions.IsEmpty())
	{
		for (const auto Transition : CurrentStateTransitions)
		{
			if(Transition && Transition->Condition())
			{
				return Transition;
			}
		}
	}

	return nullptr;
}


// Called every frame
void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(const UTransition* ActiveTransition = GetTransition())
	{
		SetCurrentState(ActiveTransition->ToState);
		
	}
	if (CurrentState) CurrentState->UpdateTick(DeltaTime);
}

