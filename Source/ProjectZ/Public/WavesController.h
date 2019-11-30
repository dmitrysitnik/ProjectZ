// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 class helper to process waves in a game session. Provide the functionality to change count, spawn rate ant other.
 */
class PROJECTZ_API WavesController
{
public:
    //Constructor of the class
	WavesController(unsigned int waveCount);
    
    //Count spawned enemies
    void AddSpawnEnemy();
    
    //Get the flag out from class
    FORCEINLINE bool IsCanSpawn() const { return bCanSpawn; } ;
    
    //Method to control Wave spawn out of class
    FORCEINLINE void SetCanSpawn(bool bSpawn){ bCanSpawn = bSpawn; };
    
    
    FORCEINLINE unsigned int GetSpawnedEnemies() const { return mCurrentSpawned; };
    
    
protected:
    
    //Properties for control
    unsigned int mEnemiesInWave;
    
    
    //Counter of spawned enemies
    unsigned int mCurrentSpawned = 0;
    
    
    //Flag to control spawn process
    bool bCanSpawn;
    
    
    //Check if the wave has ended
    void CheckWaveEnd();
};
