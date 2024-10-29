// Copyright Epic Games, Inc. All Rights Reserved.

#include "PersonalUEWikiGameMode.h"
#include "PersonalUEWikiCharacter.h"
#include "UObject/ConstructorHelpers.h"

APersonalUEWikiGameMode::APersonalUEWikiGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
