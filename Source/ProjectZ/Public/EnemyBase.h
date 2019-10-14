// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.generated.h"

UCLASS()
class PROJECTZ_API AEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBase();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    
    //Ref to class that will be spawned by spawnVolume
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	TSubclassOf<class AActor> enemyToSpawn;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UMovementComponent* movement;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    
    UPROPERTY(Category = Effects, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UParticleSystem* particleSystem;
    
    UPROPERTY(EditAnywhere, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
    class USoundBase* mExplosionSound;
    
    
    void DestroyEnemy();

    

};
