// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"

// Sets default values
APlanet::APlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlanetMesh(TEXT("/Game/Geometry/Meshes/Shape_Sphere.Shape_Sphere"));
    
    //Create the mesh component
    smPlanet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMesh"));
    RootComponent = smPlanet;
    smPlanet->SetStaticMesh(PlanetMesh.Object);
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    
    /**Make the actor move to the bottom of a screen*/
    FVector newLocation = GetActorLocation() + GetActorForwardVector()* -1 * DeltaTime * 100;
    SetActorLocation(newLocation);
}

