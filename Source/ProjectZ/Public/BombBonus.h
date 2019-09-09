// Fill out your copyright notice in the Description page of Project Settings.

//#pragma once
//
//#include "CoreMinimal.h"
//#include "BonusBase.h"
//#include "Components/SphereComponent.h"
//#include "BombBonus.generated.h"
//
///**
// * 
// */
//UCLASS()
//class PROJECTZ_API ABombBonus : public ABonusBase
//{
//    GENERATED_BODY()
//    
//    ABombBonus() : ABonusBase(){
//        ExplosionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere0"));
//        RootComponent = ExplosionSphere;
//    }
//    
//    
//    /** Restrict of the explosion area */
//    USphereComponent* ExplosionSphere;
//    
//public:
//    
//    /** Make an explosion. Destroy all enemies in the explosion area*/
//    void MakeExplosion();
//    
//};
