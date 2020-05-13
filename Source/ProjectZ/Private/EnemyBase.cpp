// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/EnemyBase.h"
#include "Sound/SoundBase.h"
#include "../ProjectZGameMode.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Health = 1.0f;

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
    newLocation.X -= 10;
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


