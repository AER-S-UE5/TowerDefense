// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UVerticalBox;
class UMenuButton;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* Container;
	
	UPROPERTY(meta=(BindWidget))
	UMenuButton* PlayButton;

	UPROPERTY(EditDefaultsOnly,Category="Buttons")
	TSubclassOf<UMenuButton> MenuButtonClass;

	UFUNCTION()
	void Continue();
};
