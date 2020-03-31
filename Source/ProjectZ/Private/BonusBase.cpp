// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusBase.h"
#include "Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"


// Sets default values
ABonusBase::ABonusBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BonusMesh(TEXT("/Game/Geometry/Meshes/Bonus_SM.Bonus_SM"));
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> BonusSkelet(TEXT("/Game/Geometry/Meshes/SK_Bonus.SK_Bonus"));
    
    //Create the mesh component
    skMeshBonus = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    
    skMeshBonus->SetGenerateOverlapEvents(true);
    
    RootComponent = skMeshBonus;
    
    mPlaceForIdleShining = CreateDefaultSubobject<USceneComponent>(TEXT("IdleParticleComponent"));
    
    //    SmBonus->SetStaticMesh(BonusMesh.Object);
    skMeshBonus->SetSkeletalMesh(BonusSkelet.Object);
    
    
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere0"));
    SphereComponent->InitSphereRadius(30.0f);
    SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABonusBase::BeginPlay()
{
	Super::BeginPlay();
    
    if(mBonusIdleShining){
        FVector emitterLocation = GetActorLocation();
        
        UGameplayStatics::SpawnEmitterAttached(mBonusIdleShining, skMeshBonus, TEXT("idleShining"), FVector(0,0,150), FRotator(-90,0,90), EAttachLocation::KeepRelativeOffset);
    }
}

// Called every frame
void ABonusBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    FVector newLocation = GetActorLocation() + GetActorForwardVector()* -1 * DeltaTime * 400;
    SetActorLocation(newLocation);

}


void ABonusBase::ApplyBonus(){
    if (mBonusSound) {
        UGameplayStatics::PlaySoundAtLocation(this, mBonusSound, GetActorLocation());
    }
    
    if(mBonusPickedUp){
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mBonusPickedUp, GetActorLocation());
    }
}



void ABonusBase::RewriteMaterial(){
    if(MaterialToRewrite){
        skMeshBonus->SetMaterial(0, MaterialToRewrite);
    }
}
