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
    
    UPROPERTY(Category = Shooting, EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class AProjectZProjectile> ProjectileToSpawn;
    
    UPROPERTY(Category = Shooting, EditAnywhere, BlueprintReadWrite)
    float FireRate;
    
    UPROPERTY(Category = Shooting, EditAnywhere, BlueprintReadWrite)
    FVector GunOffset;
    
    virtual void Tick(float deltaSeconds) override;
    
    virtual void FireShot();
    
    virtual void BeginPlay() override;
    
    FTimerHandle TimerHandle_FireTimerExpired;
    
    void FireTimerExpired();
    
    
    
protected:
    bool bCanFire;
    
	
};
