// Copyright Epic Games, Inc. All Rights Reserved.

#include "SurvivorGameMode.h"
#include "SurvivorPlayerController.h"
#include "SurvivorCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASurvivorGameMode::ASurvivorGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASurvivorPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}