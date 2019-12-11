// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "MyUserDefinedEnum.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API UMyUserDefinedEnum : public UUserDefinedEnum
{
	GENERATED_BODY()
	
    public:
    enum WaveState{
        Empty,
        Wave,
        WaveEnd,
        Boss
    };
    
};
