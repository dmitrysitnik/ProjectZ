// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "AsteroidEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API AAsteroidEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	AAsteroidEnemy();

		virtual void Tick(float deltaSeconds) override;
    
    
    
		UPROPERTY(EditAnywhere, Category = "Look")
			class UStaticMeshComponent* smEnemy;
        
    
    //Calling function on Hit Event
		UFUNCTION()
			void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
        UFUNCTION()
            void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
};
