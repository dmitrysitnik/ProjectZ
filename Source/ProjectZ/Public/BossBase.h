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
        Health = 100.0f;
    }
    
    UPROPERTY(Category = Settings, EditAnywhere, BlueprintReadWrite)
    float Health;
    
    
    virtual void BeginPlay() override;
    
    virtual void InputDamage(float damage);
	
};
