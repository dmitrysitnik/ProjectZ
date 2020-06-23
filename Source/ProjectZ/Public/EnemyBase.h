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
    
    UPROPERTY(Category = Settings, EditAnywhere, BlueprintReadWrite)
    float Speed;
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    //Function to destroy the enemy and play effects and others
    virtual void DestroyEnemy();
    
    // Sets default values for this actor's properties
    AEnemyBase();
    
    virtual void InputDamage(float damage);

    UFUNCTION()
    virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    virtual void MoveToBottom();
    
    UPROPERTY(VisibleAnywhere, Category = "Movement")
    class UMovementComponent* movement;
    
    class AProjectZGameMode* mGameMode;
    
    //The award for the enemy destroy
    int mPointsAward = 20;
    
};
