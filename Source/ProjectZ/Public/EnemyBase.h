// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.generated.h"

UCLASS()
class PROJECTZ_API AEnemyBase : public AActor
{
    GENERATED_BODY()
    
public:
    
    UPROPERTY(EditAnywhere, Category = "Look")
    class UStaticMeshComponent* smEnemy;
    
    UPROPERTY(Category = Effects, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UParticleSystem* particleSystem;
    
    UPROPERTY(EditAnywhere, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
    class USoundBase* mExplosionSound;
    
    
    UPROPERTY(Category = Settings, EditAnywhere, BlueprintReadWrite)
    float Health;
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    //Function to destroy the enemy and play effects and others
    void DestroyEnemy();
    
    // Sets default values for this actor's properties
    AEnemyBase();
    
    virtual void InputDamage(float damage);
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    virtual void MoveToBottom();
    
    //Ref to class that will be spawned by spawnVolume
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    TSubclassOf<class AActor> enemyToSpawn;
    
    UPROPERTY(VisibleAnywhere, Category = "Movement")
    class UMovementComponent* movement;
    
    class AProjectZGameMode* mGameMode;
    
    //The award for the enemy destroy
    int mPointsAward = 20;
    
};
