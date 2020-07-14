// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectZProjectile.h"
#include "EnemyProjectile.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTZ_API AEnemyProjectile : public AProjectZProjectile
{
	GENERATED_BODY()


	public:
	AEnemyProjectile();

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
