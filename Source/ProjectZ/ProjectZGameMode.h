// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Public/MyEnum.h"
#include "ProjectZGameMode.generated.h"

UCLASS(MinimalAPI)
class AProjectZGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectZGameMode();
    
    /** Method to Restart a level*/
    void RestartLevel(UObject* world, FName levelName);
    
        UFUNCTION(BlueprintCallable)
        void SetNewState(int state);
    
    
    UFUNCTION(BlueprintCallable)
    FORCEINLINE int GetState() const { return CurrentState; } ;
    
    UFUNCTION(BlueprintCallable)
    FORCEINLINE int GetPoints() const { return mPoints; };
    
    UFUNCTION(BlueprintCallable)
    void AddPoints(int points);

    UFUNCTION(BlueprintCallable)
    FORCEINLINE int GetWaveLevel(){ return Level; };

    UFUNCTION()
    void IncreaseWaveLevel();
    
    
    virtual void BeginPlay();
        
        
    private:
    
    int CurrentState = UMyEnum::WaveState::Empty;
    
    //Current points in the session
    int mPoints = 0;

    //Wave level 
    int Level = 0;

    
    class ASpaceShip* Player;
    
    float StateTime = 2.5f;
    
    void StateTimerExpired();
    
    FTimerHandle StateTimerHandle;
};



