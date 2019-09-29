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
    CheckWaveEnd();
    mCurrentSpawned++;
}


void WavesController::CheckWaveEnd(){
    //if wave has ended turn off the spawn flag and reset the  counter of spawned enemies
    if(mCurrentSpawned >= mEnemiesInWave){
        bCanSpawn = false;
        mCurrentSpawned = 0;
    }
}




