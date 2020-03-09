// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowBonus.h"
#include "SpaceShip.h"




void ASlowBonus::ApplyBonus(){
    if(!mSpaceShip) return;
    
    mSpaceShip->SetSpaceshipMoveSpeed(mDuration);
}


void ASlowBonus::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
    
    
    if(OtherActor){
        ASpaceShip* player = Cast<ASpaceShip>(OtherActor);
        
        
        if(player){
            
            //Save the player reference to use in future
            mSpaceShip = player;
            
            ApplyBonus();
            Destroy();
        }
    }
   
}




