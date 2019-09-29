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
    
    //Count spawned enemies
    void AddSpawnEnemy();
    
    
    FORCEINLINE bool IsCanSpawn() const { return bCanSpawn; } ;
    FORCEINLINE void SetCanSpawn(bool bSpawn){ bCanSpawn = bSpawn; };
    
    
protected:
    
    //Properties for control
    unsigned int mEnemiesInWave = 30;
    unsigned int mCurrentSpawned = 0;
    
    //reference to the current world
    UWorld* World;
    
    
    //Flag to control spawn process
    bool bCanSpawn;
    
    
    //Check if the wave has ended
    void CheckWaveEnd();
};
