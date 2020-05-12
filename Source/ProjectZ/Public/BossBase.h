// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "BossBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API ABossBase : public AEnemyBase
{
	GENERATED_BODY()
    
    
    
public:
    ABossBase():AEnemyBase(){
        
    }
    
    
    
    virtual void BeginPlay() override;
    
    
	
};
