// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBonus.h"
#include "SpaceShip.h"


void AShieldBonus::ApplyBonus(){
    //Temp implemantation for a check applying
    UE_LOG(LogTemp, Warning, TEXT("Bonus applied"));
    
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
            
            //Apply bonus to the player
            ApplyBonus();
            Destroy();
            
        }
    }
    
}

