// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectZProjectile.h"
#include "PlayerProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API APlayerProjectile : public AProjectZProjectile
{
	GENERATED_BODY()
	
    
    virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
