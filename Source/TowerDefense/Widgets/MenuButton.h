// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuButton.generated.h"

DECLARE_DELEGATE(OnClick)

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UMenuButton : public UUserWidget
{
	GENERATED_BODY()
public:
	OnClick OnClickDelegate;
protected:
	virtual void NativeOnInitialized() override;
private:

	UPROPERTY(meta=(BindWidget))
	UButton* Button;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text;

	UFUNCTION()
	void OnButtonClick();
};
