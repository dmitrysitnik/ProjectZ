// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "ShieldBonus.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API AShieldBonus : public ABonusBase
{
	GENERATED_BODY()
    
public:
    AShieldBonus() : ABonusBase(){
        //Add function to process overlapping
        skMeshBonus->OnComponentBeginOverlap.AddDynamic(this, &AShieldBonus::OnBeginOverlap);
        
        mDuration = 5.0f;
    };
    
    
    UPROPERTY(EditAnywhere, Category = "Settings")
    float mDuration;
    
    virtual void BeginPlay() override;
    
protected:
    //reference to the player's ship
    class ASpaceShip* mSpaceShip;
    
    /** Apply this bonus */
    virtual void ApplyBonus() override;
    
    /** Function called on the begin of overlaping*/
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
	
};
