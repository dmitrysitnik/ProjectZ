// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTZ_API WavesController
{
public:
	WavesController(UWorld* world);
	~WavesController();
    
protected:
    //Timer to handle spawn process
    FTimerHandle TimerHandle_WaveTimer;
    
    
    UWorld* World;
};
