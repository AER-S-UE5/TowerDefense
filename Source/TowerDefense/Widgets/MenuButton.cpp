// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"



void UMenuButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddDynamic(this, &UMenuButton::OnButtonClick);
}

void UMenuButton::OnButtonClick()
{
	OnClickDelegate.Execute();
}
