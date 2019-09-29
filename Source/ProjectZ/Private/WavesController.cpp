// Fill out your copyright notice in the Description page of Project Settings.


#include "WavesController.h"

WavesController::WavesController(UWorld* world)
{
    World = world;
}

WavesController::~WavesController()
{
    delete World;
}


void WavesController::AddSpawnEnemy(){
    mCurrentSpawned++;
    
    
    if(mCurrentSpawned >= mEnemiesInWave){
        bCanSpawn = false;
        
        
    }
}




