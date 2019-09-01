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

		UPROPERTY()
			class UStaticMeshComponent* smEnemy;


		UFUNCTION()
			void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
			void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
