// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/EnemyBase.h"
#include "Sound/SoundBase.h"
#include "../ProjectZGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShip.h"



// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Health = 1.0f;
    Speed = 10.0f;

    // smEnemy->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
    
    mGameMode = Cast<AProjectZGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    MoveToBottom();
}


void AEnemyBase::DestroyEnemy(){
    
    if(particleSystem){
     UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particleSystem, GetActorLocation());
    }
    
    if(mExplosionSound) {
        UGameplayStatics::PlaySoundAtLocation(this, mExplosionSound, GetActorLocation());
    }
    
    Destroy();
    
    
    //Add award points
    if(mGameMode){
        mGameMode->AddPoints(mPointsAward);
    }
    
    
}


void AEnemyBase::MoveToBottom(){
    FVector newLocation = GetActorLocation();
    newLocation.X -= Speed;
    SetActorLocation(newLocation);
}


void AEnemyBase::InputDamage(float damage){
    if (Health > damage){
        Health -= damage;
    }
    else{
        DestroyEnemy();
    }
    
}


void AEnemyBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
    //destroy player's ship. We just turn off the input and set the actor of a player to be hidden
    // if (OtherActor)
    // {
    //     //Check if the actor is a player's spaceship
    //     ASpaceShip* spaceShip = Cast<ASpaceShip>(OtherActor);
    //     if (spaceShip)
    //     {
    //         /** Set the actor to be hidden */
    //         spaceShip->Death();
    //         //Get the player controller and turn off the input
    //         APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    //         playerController->DisableInput(playerController);
    //         DestroyEnemy();
    //     }
    // }
}


