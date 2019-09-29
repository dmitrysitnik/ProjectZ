// Fill out your copyright notice in the Description page of Project Settings.


#include "WavesController.h"

WavesController::WavesController(unsigned int mCount)
{
    mEnemiesInWave = mCount;
}

WavesController::~WavesController()
{
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




