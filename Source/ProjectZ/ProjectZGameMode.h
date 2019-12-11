// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Public/MyUserDefinedEnum.h"
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
        
        
    private:
        int CurrentState = UMyUserDefinedEnum::WaveState::Empty;
    
    
    float StateTime = 2.5f;
    
    void StateTimerExpired();
    
    FTimerHandle StateTimerHandle;
};



