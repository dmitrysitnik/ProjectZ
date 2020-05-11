// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "AsteroidBoss.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API AAsteroidBoss : public ABossBase
{
	GENERATED_BODY()
    
public:
    AAsteroidBoss();
//        PrimaryActorTick.bCanEverTick = true;
//
//        static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Geometry/Meshes/SM_Rock.SM_Rock"));
//
//        smEnemy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidBossMesh"));
//
//        RootComponent = smEnemy;
//
//        smEnemy->SetStaticMesh(Mesh.Object);
//    }
	
};
