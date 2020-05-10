// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/ShootingEnemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "SpaceShip.h"
#include "Engine/StaticMesh.h"

#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"



//AShootingEnemy::AShootingEnemy(){
//    PrimaryActorTick.bCanEverTick = true;
//    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Geometry/Meshes/SM_Rock.SM_Rock"));
//    smEnemy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShootingMesh"));
//    RootComponent = smEnemy;
//    smEnemy->SetStaticMesh(Mesh.Object);
//}
//
//AShootingEnemy::~AShootingEnemy(){
//
//}
//
//
//void AShootingEnemy(float deltaSeconds){
//
//}


AShootingEnemy::AShootingEnemy(){
    PrimaryActorTick.bCanEverTick = true;
        static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Geometry/Meshes/SM_Rock.SM_Rock"));
        smEnemy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShootingMesh"));
        RootComponent = smEnemy;
        smEnemy->SetStaticMesh(Mesh.Object);
}


void AShootingEnemy::Tick(float deltaSeconds){
    Super::Tick(deltaSeconds);
    
    
    
}
