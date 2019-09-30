// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "SpawnVolume.generated.h"

UCLASS()
class PROJECTZ_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* WhereToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TArray<TSubclassOf<class AActor>> WhatToSpawn;
    
    
    

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    //The current spawn rate
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float SpawnRate;
    
    
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float SpawnEnemiesPause;
    
    
    UPROPERTY(EditAnywhere, Category = "Spawning")
    unsigned int mEnemiesInWave;
    
    
    /** Gets the one of all actors to spawn  */
    UFUNCTION()
    int32 GetRandomIndexOfToSpawn();
    
    /*Class to control waves in the game */
    class WavesController* WavesHelper;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    
    //Bounds of the box to spawn
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

    //Get random point in the box volume
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();
    
    //Function to call on timer expired
    void SpawnTimerExpired();
    
    //Function to call timer expired
    void WavePauseTimerExpired();
    
    //Timer to handle spawn process
    FTimerHandle TimerHandle_SpawnTimer;
    
    //Timer to handle waves spawn process
    FTimerHandle TimerHandle_WavePauseTimer;


private:
    //Spawn function
	void Spawn();
    
    //Can spawn flag
    bool bCanSpawn;

};
