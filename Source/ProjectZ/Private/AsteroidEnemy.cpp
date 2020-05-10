// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AsteroidEnemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "SpaceShip.h"
#include "Engine/StaticMesh.h"

#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"


AAsteroidEnemy::AAsteroidEnemy() {
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Geometry/Meshes/SM_Rock.SM_Rock"));
    
	smEnemy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidMesh"));
    
    RootComponent = smEnemy;
    
	smEnemy->SetStaticMesh(Mesh.Object);
    
	smEnemy->OnComponentBeginOverlap.AddDynamic(this, &AAsteroidEnemy::OnBeginOverlap);
	smEnemy->OnComponentHit.AddDynamic(this, &AAsteroidEnemy::OnHit);
    
    
}

void AAsteroidEnemy::Tick(float deltaSeconds) {

	Super::Tick(deltaSeconds);

	/**Make the actor move to the bottom of a screen*/
//	FVector newLocation = GetActorLocation() + GetActorForwardVector()* -1 * deltaSeconds * 600;
    
    
/** Moved to the base class*/
//    FVector newLocation = GetActorLocation();
//    newLocation.X -= 10;
//
//	SetActorLocation(newLocation);
    
}


void AAsteroidEnemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

    //destroy player's ship. We just turn off the input and set the actor of a player to be hidden
	if (OtherActor)
	{
        //Check if the actor is a player's spaceship
		ASpaceShip* spaceShip = Cast<ASpaceShip>(OtherActor);
		if (spaceShip)
		{
            spaceShip->Death();
            //Get the player controller and turn off the input
            APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
            playerController->DisableInput(playerController);

            DestroyEnemy();
		}
	}

}


void AAsteroidEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
    
    //destroy player's ship. We just turn off the input and set the actor of a player to be hidden
    if (OtherActor)
    {
        //Check if the actor is a player's spaceship
        ASpaceShip* spaceShip = Cast<ASpaceShip>(OtherActor);
        if (spaceShip)
        {
            /** Set the actor to be hidden */
            spaceShip->Death();
            //Get the player controller and turn off the input
            APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
            playerController->DisableInput(playerController);
            DestroyEnemy();
        }
    }
    
}


void AAsteroidEnemy::BeginPlay(){
    Super::BeginPlay();
    
    //Set a random rotation
    SetActorRotation(UKismetMathLibrary::RandomRotator());
    
    float randomSizeXYZ = UKismetMathLibrary::RandomFloatInRange(minAsteroidSize, maxAsteroidSize);
    SetActorScale3D(FVector(randomSizeXYZ, randomSizeXYZ, randomSizeXYZ));
}
