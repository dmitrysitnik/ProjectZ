// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "ShootingEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API AShootingEnemy : public AEnemyBase
{
	GENERATED_BODY()
    
    public:
    AShootingEnemy();
    
    
    virtual void Tick(float deltaSeconds) override;
    
	
};
