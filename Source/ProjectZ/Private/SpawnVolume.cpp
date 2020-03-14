// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpawnVolume.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "TimerManager.h"
#include "EnemyBase.h"
#include "AsteroidEnemy.h"
#include "WavesController.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectZGameMode.h"
#include "MyEnum.h"
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
    
    //Init waves helper's properties because after restart should star over 
    WavesHelper->Init();
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
    
    APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    ASpaceShip* ship = Cast<ASpaceShip>(pawn);
    
    //if ship reference is null we should return
    if(!ship) return;
    
    //Spawn decorative planets
    SpawnPlanet();
    
    if(WavesHelper->GetSpawnedEnemies() == 0 && WavesHelper->IsCanSpawn()){
        gameMode->SetNewState(UMyEnum::Wave);
    }
    
    //Check if we can create a new actor in the game
	if (WhatToSpawn.Last() != nullptr && bCanSpawn && WavesHelper->IsCanSpawn())
	{
        //Get a pointer to the current world
        UWorld* world = GetWorld();
        
        //Spawn actor from arrays to spawn(Enemies, Bonuses)
		AActor* spawnedActor = world->SpawnActor<AActor>(GetActorToSpawn(), GetRandomPointInVolume(), FRotator(0.0f, 0.0f, 0.0f));
        
        //Count the enemies
        AEnemyBase* enemy = Cast<AEnemyBase>(spawnedActor);
        
        
        if(enemy && WavesHelper->IsCanSpawn()){
            WavesHelper->AddSpawnEnemy();
        }
        
        
        //Wave has ended => Set new state
        if(gameMode && !WavesHelper->IsCanSpawn()){
            gameMode->SetNewState(UMyEnum::WaveEnd);
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


//Spawn a planet
void ASpawnVolume::SpawnPlanet(){
    if(!bCanSpawnPlanet) return;
    
    //Get max index of the Planet array to variable
    const int32 maxPlanets = PlanetsToSpawn.Num() - 1;
    
    FVector newPlanetPosition = GetRandomPointInVolume();
    
    //Get random planet index to spawn
    int32 planetIndex = UKismetMathLibrary::RandomIntegerInRange(0, maxPlanets);
                         
                    
    //Planet should be in the scene's back, like on distance from ship and other
    newPlanetPosition.Z = -1000;
    //TO-DO: Get random FRotator
    AActor* spawnedPlanetActor = GetWorld()->SpawnActor<AActor>(PlanetsToSpawn[planetIndex], newPlanetPosition, FRotator(0.0f, 0.0f ,0.0f));
    
    //Get a scale for XYZ axies
    float planetXYZ = UKismetMathLibrary::RandomFloatInRange(3.0f, 8.0f);
    spawnedPlanetActor->SetActorScale3D(FVector(planetXYZ, planetXYZ, planetXYZ));
    
    
    //Run Planet's timer
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_PlanetTimer, this, &ASpawnVolume::PlanetTimerExpired, PlanetSpawnRate);
    bCanSpawnPlanet = false;
}


void ASpawnVolume::PlanetTimerExpired(){
    bCanSpawnPlanet = true;
}



TSubclassOf<AActor> ASpawnVolume::GetActorToSpawn(){
    const int32 maxValue = 100;
    const int32 bonusProbability = 20;
    const int32 enemyProbability = 80;
    TSubclassOf<AActor> returnActor;
    
    int32 randomNum = UKismetMathLibrary::RandomIntegerInRange(0, maxValue);
    
    return randomNum > enemyProbability ? WhatToSpawn[GetRandomIndexOfToSpawn()] : BonusToSpawn[0];
    
}
