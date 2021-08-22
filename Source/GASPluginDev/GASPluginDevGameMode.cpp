// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASPluginDevGameMode.h"
#include "GASPluginDevCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGASPluginDevGameMode::AGASPluginDevGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
