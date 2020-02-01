// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorDeleteVolume.h"
#include "Components/BoxComponent.h"

// Sets default values
AActorDeleteVolume::AActorDeleteVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
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

}


void AActorDeleteVolume::DeleteActorsInsideBox(){
    
    TArray<AActor*> overlappedActors;
    mBox->GetOverlappingActors(overlappedActors);
    
}

