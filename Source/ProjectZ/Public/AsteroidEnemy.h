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
};
