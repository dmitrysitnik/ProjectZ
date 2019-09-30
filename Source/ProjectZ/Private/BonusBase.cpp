// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusBase.h"
#include "Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABonusBase::ABonusBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BonusMesh(TEXT("/Game/Geometry/Meshes/Bonus_SM.Bonus_SM"));
    
    //Create the mesh component
    SmBonus = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonusMesh"));
    RootComponent = SmBonus;
    SmBonus->SetStaticMesh(BonusMesh.Object);
    
    
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere0"));
    SphereComponent->InitSphereRadius(30.0f);
    SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABonusBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABonusBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    FVector newLocation = GetActorLocation() + GetActorForwardVector()* -1 * DeltaTime * 400;
    SetActorLocation(newLocation);

}


void ABonusBase::ApplyBonus(){

}

