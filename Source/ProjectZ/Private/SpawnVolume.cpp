// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpawnVolume.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Создать объект для спауна
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
    
    //Set the current spawn rate
    SpawnRate = 1.5f;
    
    //Set the spawn flag to true
    bCanSpawn = true;
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

	Spawn();
}


FVector ASpawnVolume::GetRandomPointInVolume() {

	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);

}


//Method to spawn actors in the volume
void ASpawnVolume::Spawn() {
    
	if (WhatToSpawn != nullptr && bCanSpawn)
	{
        UWorld* world = GetWorld();
        
		world->SpawnActor<AActor>(WhatToSpawn, GetRandomPointInVolume(), FRotator(0.0f, 0.0f, 0.0f));
        bCanSpawn = false;
        world->GetTimerManager().SetTimer(TimerHandle_SpawnTimer, this, &ASpawnVolume::SpawnTimerExpired, SpawnRate);
        
	}

}

//Function that set up the bCanSpawn to true value
void ASpawnVolume::SpawnTimerExpired(){
    bCanSpawn = true;
}




