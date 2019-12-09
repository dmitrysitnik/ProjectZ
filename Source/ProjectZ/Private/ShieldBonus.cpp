// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBonus.h"
#include "SpaceShip.h"
#include "../Public/MyUserDefinedEnum.h"
#include "ProjectZGameMode.h"
#include "Kismet/GameplayStatics.h"


void AShieldBonus::ApplyBonus(){
    
    Super::ApplyBonus();
    
    
    AProjectZGameMode* gameMode = Cast<AProjectZGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if(gameMode){
        gameMode->SetNewState(UMyUserDefinedEnum::Boss);
    }
    
    if(mSpaceShip){
        mSpaceShip->SetInvulnerable(true, mDuration);
    }
    
}

//Overlap functions
void AShieldBonus::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
    
    UE_LOG(LogTemp, Warning, TEXT("WE ARE YOUR FRIENDS"));
    
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

