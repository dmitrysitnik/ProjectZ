// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "AsteroidBoss.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API AAsteroidBoss : public ABossBase
{
	GENERATED_BODY()
    
public:
    AAsteroidBoss();
	
    
    //Calling function on BeginOverLap event
    virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
    
    //Calling function on Hit Event
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    virtual void DestroyEnemy() override;
    virtual void BeginPlay() override;
};



