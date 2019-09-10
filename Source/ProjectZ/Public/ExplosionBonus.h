// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "ExplosionBonus.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API AExplosionBonus : public ABonusBase
{
	GENERATED_BODY()
    
    
public:
    
    /** Make an explosion in the sphere area. Destroy all enemies actors in the area*/
    void MakeExplosion();
	
};
