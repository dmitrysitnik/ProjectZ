// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 class helper to process waves in a game session. Provide the functionality to change count, spawn rate ant other.
 */
class PROJECTZ_API WavesController
{
public:
	WavesController(UWorld* world);
	~WavesController();
    
protected:
    //Timer to handle spawn process
    FTimerHandle TimerHandle_WaveTimer;
    
    //reference to the current world
    UWorld* World;
};
