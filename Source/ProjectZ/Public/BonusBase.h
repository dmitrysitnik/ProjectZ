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
    //Sphere component to interact with actors in the boundaries
    UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class USphereComponent* SphereComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    class UMaterial* MaterialToRewrite;
    
    
    //Particle component to visualize apply
    UPROPERTY(Category = Effects, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UParticleSystem* ParticleSystem;
    
    
    //The bonus sound's appies component
    UPROPERTY(EditAnywhere, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
    class USoundBase* mBonusSound;
    
    UPROPERTY(EditAnywhere, Category = "Appearance")
    class USceneComponent* mPlaceForIdleShining;
    
    //The skeletal mesh
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class USkeletalMeshComponent* skMeshBonus;
    
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UParticleSystem* mBonusPickedUp;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UParticleSystem* mBonusIdleShining;
    
    
	// Sets default values for this actor's properties
	ABonusBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    //virtual function to override in inherited classes which applies a class bonus
    virtual void ApplyBonus();
    
    virtual void RewriteMaterial();
    
    
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    

};
