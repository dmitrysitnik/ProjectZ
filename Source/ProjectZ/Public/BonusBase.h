// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BonusBase.generated.h"

//  virtual class of a base bonus
UCLASS()
class PROJECTZ_API ABonusBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonusBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    //virtual function to override in inherited classes which applies a class bonus
    virtual void ApplyBonus();
    
    
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    
    //Sphere component to interact with actors in the boundaries
    UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class USphereComponent* SphereComponent;
    
    
    //Particle component to visualize apply
    UPROPERTY(Category = Effects, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UParticleSystem* ParticleSystem;
    
    
    //Static mesh component to make different shape bonuses
    UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* SmBonus;
    
    
    //The bonus sound's appies component
    UPROPERTY(EditAnywhere, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
    class USoundBase* mBonusSound;
    
    
    
    //The skeletal mesh
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class USkeletalMeshComponent* skMeshBonus;
    
    
    
    UPROPERTY()
    class USceneComponent* scene;
    
    

};
