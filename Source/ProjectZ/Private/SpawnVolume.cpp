// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpawnVolume.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "TimerManager.h"
#include "WavesController.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a box volume to spawn actors
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
    
    //Set the current spawn rate
    SpawnRate = 1.5f;
    
    //Set the spawn flag to true
    bCanSpawn = true;
    
    //Create waveController instance
    WavesController = new class WavesController(GetWorld());
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    // Call the spawning function
	Spawn();
}


FVector ASpawnVolume::GetRandomPointInVolume() {

	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);

}


//Method to spawn actors in the volume
void ASpawnVolume::Spawn() {
    //Check if we can create a new actor in the game
	if (WhatToSpawn.Last() != nullptr && bCanSpawn)
	{
        //Get a pointer to the current world
        UWorld* world = GetWorld();
        //Spawn actor
		world->SpawnActor<AActor>(WhatToSpawn[GetRandomIndexOfToSpawn()], GetRandomPointInVolume(), FRotator(0.0f, 0.0f, 0.0f));
        
        //Set bCanSpawn to false and invoke the SpawnTimer
        bCanSpawn = false;
        world->GetTimerManager().SetTimer(TimerHandle_SpawnTimer, this, &ASpawnVolume::SpawnTimerExpired, SpawnRate);
        
	}

}

//Function that set up the bCanSpawn to true value
void ASpawnVolume::SpawnTimerExpired(){
    bCanSpawn = true;
}


int32 ASpawnVolume::GetRandomIndexOfToSpawn(){
    //Get the number of WhatToSpawn array
    int32 maxValue = WhatToSpawn.Num() - 1;
    //Return a number between zero and maxValue variable
    return maxValue > 0 ? UKismetMathLibrary::RandomIntegerInRange(0, maxValue) : 0;
    
}




