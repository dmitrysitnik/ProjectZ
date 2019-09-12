// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionBonus.h"
#include "Components/SphereComponent.h"
#include "EnemyBase.h"



void AExplosionBonus::MakeExplosion(){
    
    TArray<AActor*> overlappedActors;
    SphereComponent->GetOverlappingActors(overlappedActors);
    
    
    for (int current = 0; current < overlappedActors.Num(); current++) {
        
        AActor* currentActor = overlappedActors[current];
        
        if(currentActor){
            
            AEnemyBase* enemy = Cast<AEnemyBase>(currentActor);
            
            if(enemy){
                enemy->Destroy();
                UE_LOG(LogTemp, Warning, TEXT("Destroy an actor from explosion"));
            }
            
        }
    }
    
}




void AExplosionBonus::ApplyBonus(){
    MakeExplosion();
}


void AExplosionBonus::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
    
    ApplyBonus();
}

