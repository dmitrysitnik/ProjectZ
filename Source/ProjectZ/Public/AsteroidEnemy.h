// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "AsteroidEnemy.generated.h"

/**
 *
 */
UCLASS()
class PROJECTZ_API AAsteroidEnemy : public AEnemyBase
{
    GENERATED_BODY()
    
public:
    AAsteroidEnemy();
    
    virtual void Tick(float deltaSeconds) override;
    
    
    
    
    UPROPERTY(EditAnywhere, Category = "Look")
    float minAsteroidSize = 0.6f;
    
    
    UPROPERTY(EditAnywhere, Category = "Look")
    float maxAsteroidSize = 1.2f;
    
    class USceneComponent* scene;
    
    
    void BeginPlay() override;
    
    
    
    //Calling function on Hit Event
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    
    //Calling function on BeginOverLap event
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    
};
