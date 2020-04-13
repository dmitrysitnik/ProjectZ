// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionBonus.h"
#include "Components/SphereComponent.h"
#include "SpaceShip.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyBase.h"
#include "../Public/MyEnum.h"
#include "ProjectZGameMode.h"

void AExplosionBonus::MakeExplosion(){
    
    // play effect of the explosion
    if(ParticleSystem){
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation());
    }
    
    //Get the overlapping actors from sphere component
    TArray<AActor*> overlappedActors;
    SphereComponent->GetOverlappingActors(overlappedActors);
    
    //    Check all overlapped actors
    for (int current = 0; current < overlappedActors.Num(); current++) {
        
        //Get the current actor
        AActor* currentActor = overlappedActors[current];
        
        //Check if the actor is not null
        if(currentActor){
            
            //Try convert the actor to an enemy actor
            AEnemyBase* enemy = Cast<AEnemyBase>(currentActor);
            if(enemy){
                //Destroy the actor
                enemy->DestroyEnemy();
            }
            
        }
    }
    
}

void AExplosionBonus::ApplyBonus(){
    
    Super::ApplyBonus();
    
    //Create an explosion in the sphere raduis
    MakeExplosion();
    
    AProjectZGameMode* gameMode = Cast<AProjectZGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if(gameMode){
        gameMode->SetNewState(UMyEnum::Empty);
    }
}

void AExplosionBonus::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
    
    
    if(OtherActor){
        ASpaceShip* player = Cast<ASpaceShip>(OtherActor);
        
        if(player){
            ApplyBonus();
            Destroy();
        }
    }
   
}


void AExplosionBonus::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
    SphereComponent->SetSphereRadius(SphereRadius);
}


void AExplosionBonus::BeginPlay(){
    Super::BeginPlay();
    RewriteMaterial();
}

