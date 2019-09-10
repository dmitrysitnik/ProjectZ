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
        SmBonus->OnComponentBeginOverlap.AddDynamic(this, &AShieldBonus::OnBeginOverlap);
    };
    
protected:
    /** Apply this bonus */
    virtual void ApplyBonus() override;
    
    /** Function called on the begin of overlaping*/
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
	
};
