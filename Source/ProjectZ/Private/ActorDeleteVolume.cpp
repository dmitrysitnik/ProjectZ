// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorDeleteVolume.h"
#include "Components/BoxComponent.h"

// Sets default values
AActorDeleteVolume::AActorDeleteVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    
    //Create the box component
    mBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent0"));
  
}

// Called when the game starts or when spawned
void AActorDeleteVolume::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActorDeleteVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    DeleteActorsInsideBox();
}



//Method that delete actors in the box component
void AActorDeleteVolume::DeleteActorsInsideBox(){
    //Get all actors inside box component
    TArray<AActor*> overlappedActors;
    mBox->GetOverlappingActors(overlappedActors);
    
    //Delete all actors
    for(auto actor : overlappedActors){
        actor->Destroy();
    }
    
}

