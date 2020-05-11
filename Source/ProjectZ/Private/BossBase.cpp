// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBase.h"

void ABossBase::BeginPlay(){
    Super::BeginPlay();
}

void ABossBase::InputDamage(float damage){
    if (Health > damage){
        Health -= damage;
    }
    else{
        DestroyEnemy();
    }
    
}

