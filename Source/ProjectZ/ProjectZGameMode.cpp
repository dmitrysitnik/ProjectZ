// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectZGameMode.h"
#include "ProjectZPawn.h"

AProjectZGameMode::AProjectZGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AProjectZPawn::StaticClass();
}

