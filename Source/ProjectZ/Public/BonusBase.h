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
    
    
    virtual void ApplyBonus();
    
    
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    
    UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class USphereComponent* SphereComponent;
    
    
    UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* SmBonus;
    
    

};
