// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "Components/SphereComponent.h"
#include "ExplosionBonus.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API AExplosionBonus : public ABonusBase
{
	GENERATED_BODY()
    
    
public:
    /** Constructor*/
    AExplosionBonus() : ABonusBase(){
        //Add function to process overlapping
        SmBonus->OnComponentBeginOverlap.AddDynamic(this, &AExplosionBonus::OnBeginOverlap);
        SphereComponent->SetSphereRadius(50.0f);
    };
    
    
    /** Make an explosion in the sphere area. Destroy all enemies actors in the area*/
    void MakeExplosion();
	
    
    /** Apply the bonus*/
    virtual void ApplyBonus() override;
    
    /** Function called on the overlapping event's begin*/
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    
};
