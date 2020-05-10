// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/ShootingEnemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "SpaceShip.h"
#include "Engine/StaticMesh.h"
#include "ProjectZProjectile.h"
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
    
    
    GunOffset = FVector(-20.0f, 0.0f, 0.0f);
    FireRate = 2.0f;
    
}


void AShootingEnemy::Tick(float deltaSeconds){
    Super::Tick(deltaSeconds);
    
    
    FireShot();
}

void AShootingEnemy::BeginPlay(){
    Super::BeginPlay();
    bCanFire = true;
    
}



void AShootingEnemy::FireShot(){
    // If it's ok to fire again
    if (bCanFire == true)
    {

        const FRotator FireRotation = -1 * GetActorRotation();
        //Spawn projectile at an offset from this pawn
        const FVector SpawnLocation = GetActorLocation() + GunOffset;

        UWorld* const World = GetWorld();
        if (World && ProjectileToSpawn)
        {
            //spawn the projectile
            World->SpawnActor<AProjectZProjectile>(ProjectileToSpawn, SpawnLocation, FireRotation);


            bCanFire = false;
            World->GetTimerManager().SetTimer(TimerHandle_FireTimerExpired, this, &AShootingEnemy::FireTimerExpired, FireRate);

            //try and play the sound if specified
            //               if (FireSound)
            //               {
            //                   UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
            //               }

            bCanFire = false;
        }
    }
}


void AShootingEnemy::FireTimerExpired(){
    bCanFire = true;
}
