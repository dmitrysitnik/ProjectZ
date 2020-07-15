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


AShootingEnemy::AShootingEnemy(){
    PrimaryActorTick.bCanEverTick = true;
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Geometry/Meshes/SM_Rock.SM_Rock"));
    smEnemy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShootingMesh"));
    RootComponent = smEnemy;
    smEnemy->SetStaticMesh(Mesh.Object);
    

    smEnemy->OnComponentHit.AddDynamic(this, &AShootingEnemy::OnHit);
    smEnemy->OnComponentBeginOverlap.AddDynamic(this, &AShootingEnemy::OnBeginOverlap);

    //Base GunOffset setup
    GunOffset = FVector(-200.0f, 0.0f, 0.0f);
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
    if (!bCanFire) return;
    
    
    FRotator FireRotation = GetActorRotation();
    FireRotation.Yaw = 180.0f;
    
    //Spawn projectile at an offset from this pawn
    const FVector SpawnLocation = GetActorLocation() + GunOffset;
    
    UWorld* const World = GetWorld();
    if (World && ProjectileToSpawn)
    {
        //spawn the projectile
        AProjectZProjectile *spawned = World->SpawnActor<AProjectZProjectile>(ProjectileToSpawn, SpawnLocation, FireRotation);
        
        if (!spawned){
            return;
        }

        //Set little more bigger the projectile after spawn
        spawned->SetActorScale3D(FVector(2.0f, 2.0f, 2.0f));
        
        
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


void AShootingEnemy::FireTimerExpired(){
    bCanFire = true;
}


void AShootingEnemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
    UE_LOG(LogTemp, Warning, TEXT("Hit Shooting enemy"));

    // //destroy player's ship. We just turn off the input and set the actor of a player to be hidden
	// if (OtherActor)
	// {
    //     //Check if the actor is a player's spaceship
	// 	ASpaceShip* spaceShip = Cast<ASpaceShip>(OtherActor);
	// 	if (spaceShip)
	// 	{
    //         spaceShip->Death();
    //         //Get the player controller and turn off the input
    //         // APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    //         // playerController->DisableInput(playerController);

    //         DestroyEnemy();
	// 	}
	// }
}

void AShootingEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
   //destroy player's ship. We just turn off the input and set the actor of a player to be hidden
	if (OtherActor)
	{
        //Check if the actor is a player's spaceship
		ASpaceShip* spaceShip = Cast<ASpaceShip>(OtherActor);
		if (spaceShip)
		{
            spaceShip->Death();
            //Get the player controller and turn off the input
            // APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
            // playerController->DisableInput(playerController);

            DestroyEnemy();
		}
	}
}