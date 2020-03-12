// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "SlowBonus.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API ASlowBonus : public ABonusBase
{
	GENERATED_BODY()
    
public:
    
    UPROPERTY(EditAnywhere, Category = "Settings")
    float mDuration = 5.0f;
    
    UPROPERTY(EditAnywhere, Category = "Settings")
    float mSlowSpeed = 350.0f;
    
    //On begin overlap with player will save ref to player here
    class ASpaceShip* mSpaceShip;
    
    ASlowBonus(): ABonusBase(){
        skMeshBonus->OnComponentBeginOverlap.AddDynamic(this, &ASlowBonus::OnBeginOverlap);
        
    }
    
    
    /** Apply the bonus*/
    virtual void ApplyBonus() override;
    
    virtual void BeginPlay() override;
    
    
    /** Function called on the overlapping event's begin*/
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    
	
};
