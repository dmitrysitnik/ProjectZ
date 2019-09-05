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
    
    
    /** Gets the one of all actors to spawn  */
    UFUNCTION()
    int32 GetRandomIndexOfToSpawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }


	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();
    
    
    void SpawnTimerExpired();
    
    
    FTimerHandle TimerHandle_SpawnTimer;


private:
	void Spawn();
    bool bCanSpawn;

};
