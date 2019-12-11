// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpawnVolume.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "TimerManager.h"
#include "EnemyBase.h"
#include "WavesController.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectZGameMode.h"
#include "MyUserDefinedEnum.h"
#include "SpaceShip.h"
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
    
    //Initialize the count of enemies
    mEnemiesInWave = 30.0f;
    
    //Initialize enemies pause time in seconds
    SpawnEnemiesPause = 15.0f;
    
    bCanSpawnPlanet = true; 
    
    PlanetSpawnRate = 3.0f;
    
    //Create waveController instance
    WavesHelper = new class WavesController(mEnemiesInWave);
    
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

//Get a random point in the volume
FVector ASpawnVolume::GetRandomPointInVolume() {

	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);

}


//Method to spawn actors in the volume
void ASpawnVolume::Spawn() {
    
    AProjectZGameMode* gameMode = Cast<AProjectZGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    //Stop spawn if player is dead
    
    
    APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    ASpaceShip* ship = Cast<ASpaceShip>(pawn);
    
    if(ship->IsDead()) return;
    
    if(WavesHelper->GetSpawnedEnemies() == 0 && WavesHelper->IsCanSpawn()){
        gameMode->SetNewState(UMyUserDefinedEnum::Wave);
    }
    
    //Check if we can create a new actor in the game
	if (WhatToSpawn.Last() != nullptr && bCanSpawn && WavesHelper->IsCanSpawn())
	{
        //Get a pointer to the current world
        UWorld* world = GetWorld();
        
        SpawnPlanet();
        
        //Spawn actor
		AActor* spawnedActor = world->SpawnActor<AActor>(WhatToSpawn[GetRandomIndexOfToSpawn()], GetRandomPointInVolume(), FRotator(0.0f, 0.0f ,0.0f));
        
        AEnemyBase* enemy = Cast<AEnemyBase>(spawnedActor);
        if(enemy && WavesHelper->IsCanSpawn()){
            WavesHelper->AddSpawnEnemy();
        }
        
        if(gameMode && !WavesHelper->IsCanSpawn()){
            gameMode->SetNewState(UMyUserDefinedEnum::WaveEnd);
        }
        
        //Set bCanSpawn to false and invoke the SpawnTimer
        bCanSpawn = false;
        world->GetTimerManager().SetTimer(TimerHandle_SpawnTimer, this, &ASpawnVolume::SpawnTimerExpired, SpawnRate);
        
        //Wait for next time spawn,
        if(!WavesHelper->IsCanSpawn()){
            world->GetTimerManager().SetTimer(TimerHandle_WavePauseTimer, this, &ASpawnVolume::WavePauseTimerExpired, SpawnEnemiesPause);
        }
        
	}

}

//Function that set up the bCanSpawn to true value
void ASpawnVolume::SpawnTimerExpired(){
    bCanSpawn = true;
}


//Get random index from ToSpawn array
int32 ASpawnVolume::GetRandomIndexOfToSpawn(){
    //Get the number of WhatToSpawn array
    int32 maxValue = WhatToSpawn.Num() - 1;
    //Return a number between zero and maxValue variable
    return maxValue > 0 ? UKismetMathLibrary::RandomIntegerInRange(0, maxValue) : 0;
    
}

//Functon that will be called after timer has expired
void ASpawnVolume::WavePauseTimerExpired(){
    WavesHelper->SetCanSpawn(true);
}



void ASpawnVolume::SpawnPlanet(){
    if(!bCanSpawnPlanet) return;
    
    FVector newPlanetPosition = GetRandomPointInVolume();
    newPlanetPosition.Z = -800;
    AActor* spawnedPlanetActor = GetWorld()->SpawnActor<AActor>(PlanetsToSpawn[0], newPlanetPosition, FRotator(0.0f, 0.0f ,0.0f));
    
    
    float planetXYZ = UKismetMathLibrary::RandomFloatInRange(3.0f, 8.0f);
    spawnedPlanetActor->SetActorScale3D(FVector(planetXYZ, planetXYZ, planetXYZ));
    
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_PlanetTimer, this, &ASpawnVolume::PlanetTimerExpired, PlanetSpawnRate);
    bCanSpawnPlanet = false;
}


void ASpawnVolume::PlanetTimerExpired(){
    bCanSpawnPlanet = true;
}
