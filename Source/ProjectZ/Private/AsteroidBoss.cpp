// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidBoss.h"
#include "BossBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "SpaceShip.h"
#include "Engine/StaticMesh.h"
#include "PlayerProjectile.h"

#include "../Public/MyEnum.h"
#include "ProjectZGameMode.h"

#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"

AAsteroidBoss::AAsteroidBoss() : ABossBase::ABossBase()
{
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Geometry/Meshes/SM_Rock.SM_Rock"));

    smEnemy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidBossMesh"));

    RootComponent = smEnemy;

    smEnemy->SetStaticMesh(Mesh.Object);


    smEnemy->OnComponentBeginOverlap.AddDynamic(this, &AAsteroidBoss::OnBeginOverlap);
	smEnemy->OnComponentHit.AddDynamic(this, &AAsteroidBoss::OnHit);
}

//Overlap event
void AAsteroidBoss::OnBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

    //destroy player's ship. We just turn off the input and set the actor of a player to be hidden
    if (OtherActor)
    {
        //Check if the actor is a player's spaceship
        ASpaceShip *spaceShip = Cast<ASpaceShip>(OtherActor);
        if (spaceShip) {
            /** Set the actor to be hidden */
            spaceShip->Death();
            //Get the player controller and turn off the input
            APlayerController *playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
            playerController->DisableInput(playerController);
            DestroyEnemy();
        }
        else {
            APlayerProjectile *projectile = Cast<APlayerProjectile>(OtherActor);

            if (projectile) {
                InputDamage(projectile->GetDamage());
            }
        }
    }
}

void AAsteroidBoss::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
}

void AAsteroidBoss::DestroyEnemy()
{
    Super::DestroyEnemy();

    AProjectZGameMode *gameMode = Cast<AProjectZGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    gameMode->SetNewState(UMyEnum::AfterBossFight);
}

void AAsteroidBoss::BeginPlay()
{
    Super::BeginPlay();
    SetActorScale3D(FVector(4.0f, 4.0f, 4.0f));
}
