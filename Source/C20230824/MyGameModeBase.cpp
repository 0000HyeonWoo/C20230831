// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	//Set Default Value
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
