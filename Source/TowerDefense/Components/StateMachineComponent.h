// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/Core/Public/Containers/Array.h"
#include "../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/Core/Public/Containers/Map.h"
#include "../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/RenderCore/Public/DynamicRenderScaling.h"
#include "Components/ActorComponent.h"
#include "TowerDefense/Utility/IState.h"
#include "StateMachineComponent.generated.h"


class UTransition;
class UIState;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

	

public:	
	// Sets default values for this component's properties
	UStateMachineComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UIState* GetCurrentState() const;
	void SetCurrentState(UIState* NewState);
	void AddTransition(UIState* FromState, UIState* ToState, TFunction<bool()> Func);
	void AddFromAnyTransition(UIState* ToState, TFunction<bool()> Func);

	virtual ~UStateMachineComponent() override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	
private:
	
	UPROPERTY()
	UIState* CurrentState;
	
	
	TMap<UIState*, TArray<UTransition*>> StatesTransitions;
		
	UPROPERTY()
	TArray<UTransition*> CurrentStateTransitions;

	UPROPERTY()
	TArray<UTransition*> FromAnyTransitions;

	UTransition* GetTransition() const;
};
