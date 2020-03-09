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
    
    ASlowBonus(): ABonusBase(){
        skMeshBonus->OnComponentBeginOverlap.AddDynamic(this, &ASlowBonus::OnBeginOverlap);
        
        //Set the default bonus duration
        mDuration = 5.0f;
    }
    
    
    UPROPERTY(EditAnywhere, Category = "Settings")
    float mDuration;
    
    /** Apply the bonus*/
    virtual void ApplyBonus() override;
    
    
    class ASpaceShip* mSpaceShip;
    
    /** Function called on the overlapping event's begin*/
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    
	
};
