// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBonus.h"
#include "SpaceShip.h"


void AShieldBonus::ApplyBonus(){
    
    if(mSpaceShip){
        mSpaceShip->SetInvulnerable(true, mDuration);
    }
    
}

//Overlap functions
void AShieldBonus::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
    
    //Check if we overlaped an actor
    if (OtherActor)
    {
        //Check if the actor is a player's spaceship
        ASpaceShip* spaceShip = Cast<ASpaceShip>(OtherActor);
        if (spaceShip)
        {
            
            //Save the reference to the SpaceShip
            mSpaceShip = spaceShip;
            
            //Apply bonus to the player
            ApplyBonus();
            Destroy();
        }
    }
    
}

