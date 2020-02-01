// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorDeleteVolume.generated.h"

UCLASS()
class PROJECTZ_API AActorDeleteVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorDeleteVolume();
    
    
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* mBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    void DeleteActorsInsideBox();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
