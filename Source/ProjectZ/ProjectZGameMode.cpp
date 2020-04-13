// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectZGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "../Public/MyEnum.h"
#include "ProjectZPawn.h"
#include "../Public/SpaceShip.h"

AProjectZGameMode::AProjectZGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AProjectZPawn::StaticClass();
    
}

void AProjectZGameMode::BeginPlay(){
    player = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AProjectZGameMode::RestartLevel(UObject* world, FName levelName){
    UGameplayStatics::OpenLevel(world, levelName);
}


void AProjectZGameMode::SetNewState(int state){
    CurrentState = state;
    GetWorld()->GetTimerManager().SetTimer(StateTimerHandle, this, &AProjectZGameMode::StateTimerExpired, StateTime);
}


void AProjectZGameMode::StateTimerExpired(){
    if(CurrentState != UMyEnum::Empty) SetNewState(UMyEnum::Empty);
}


void AProjectZGameMode::AddPoints(int points){
    
    
    if(player){
        if(player->IsDead()) return;
    }
    
    mPoints += points;
}



