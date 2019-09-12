// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionBonus.h"
#include "Components/SphereComponent.h"
#include "EnemyBase.h"



void AExplosionBonus::MakeExplosion(){
    
    
    //Get the overlapping actors from sphere component
    TArray<AActor*> overlappedActors;
    SphereComponent->GetOverlappingActors(overlappedActors);
    
    //    Check all overlapped actors
    for (int current = 0; current < overlappedActors.Num(); current++) {
        
        //Get the current actor from index
        AActor* currentActor = overlappedActors[current];
        
        //Check if the actor is not null
        if(currentActor){
            
            
            //Try convert the actor to an enemy actor
            AEnemyBase* enemy = Cast<AEnemyBase>(currentActor);
            if(enemy){
                //Destroy the actor
                enemy->Destroy();
            }
            
        }
    }
    
}




void AExplosionBonus::ApplyBonus(){
    
    //Create an explosion in the sphere raduis
    MakeExplosion();
    
    // Should delete the bonus from level
    Destroy();
}


void AExplosionBonus::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
    
    ApplyBonus();
}

